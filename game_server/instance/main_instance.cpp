#include "main_instance.h"
#include "common.h"
#include "dict_object.h"
#include "exeption.h"
#include "json.h"
#include "boss.h"

MainInstance::MainInstance ( GameSocket *owner ) : owner_shard ( owner )
{
    for ( uint32 i = 0; i < Packets::IG_JOIN; ++i )
    {
        _shardPacketHandlers[i].setHandler ( PacketHandler<MainInstance>::NO_HANDLER_SET, NULL );
    }
    _shardPacketHandlers[Packets::IG_JOIN].setHandler ( PacketHandler<MainInstance>::HANDLER_SET, &MainInstance::cJoin );
    _shardPacketHandlers[Packets::IG_GET_LOCATIONS_LIST].setHandler ( PacketHandler<MainInstance>::HANDLER_SET, &MainInstance::cGetLocationsInfo );
    _shardPacketHandlers[Packets::IG_START_LOCATION].setHandler ( PacketHandler<MainInstance>::HANDLER_SET, &MainInstance::cStartLocation );
    _shardPacketHandlers[Packets::IG_FINISH_LOCATION].setHandler ( PacketHandler<MainInstance>::HANDLER_SET, &MainInstance::cFinishLocation );
    _shardPacketHandlers[Packets::IG_KICK_BOSS].setHandler ( PacketHandler<MainInstance>::HANDLER_SET, &MainInstance::cKickBoss );
    _shardPacketHandlers[Packets::IG_GET_BOSS_UPDATE].setHandler ( PacketHandler<MainInstance>::HANDLER_SET, &MainInstance::cGetBossUpdate );
    _shardPacketHandlers[Packets::IG_EXCHANGE].setHandler ( PacketHandler<MainInstance>::HANDLER_SET, &MainInstance::cExchange );
    _shardPacketHandlers[Packets::IG_REQ_COLL].setHandler ( PacketHandler<MainInstance>::HANDLER_SET, &MainInstance::cReqColl );
}
User* MainInstance::getUser ( Packet* pkt )
{
    User* usr = iStorage->getOnlineUser ( pkt->sock->getSockDescriptor() );
    if ( usr == NULL )
    {
        if ( pkt->type != Packets::IG_JOIN )
        {
            emitExeption ( ErrorExeption::USER_NOT_FOUND );
        }
        else
        {
            IG_JOIN join_data = IG_JOIN::decompress ( pkt );
            usr = iStorage->loadLocalUser ( pkt->sock->getSockDescriptor(), join_data.soc_id, 0 );
        }
    }
    if ( usr == NULL )
    {
        emitExeption ( ErrorExeption::USER_NOT_FOUND );
    }
    usr->set ( "last_activity", iStorage->getCurrentTime() );
    traceerr("CurrTime = %u, ACTIVITY DETECTED = %u, uid = %u", iStorage->getCurrentTime(), usr->get("last_activity")->getInt(), usr->get("uid")->getInt());
    return usr;
}
void MainInstance::handlePacket ( Packet* pkt )
{
    User* usr = NULL;
    if ( _shardPacketHandlers[pkt->type].status == PacketHandler<MainInstance>::NO_HANDLER_SET )
    {
        Packet send_pkt = OG_ERROR::create ( 0, intToString ( MSG_PACKET_WRONG_ID_IN_THIS_INSTANCE ).c_str() );
        pkt->sock->send ( &send_pkt );
        return;
    }
    try
    {
        usr = getUser ( pkt );
        usr->lock();
        ( this->*_shardPacketHandlers[pkt->type].handler ) ( usr, pkt );
        usr->unlock();
        usr->updateClient();
        return;
    }
    catch ( ErrorExeption err_exp )
    {
        if ( usr != NULL )
            usr->unlock();
        err_exp.doCatch ( pkt );
        return;
    }
    catch ( ... )
    {
        if ( usr != NULL )
            usr->unlock();
        traceerr ( "%s", "Unknown exeption!" );
    }
}
void MainInstance::cJoin ( User* usr, Packet* pkt )
{
    usr->join ( pkt->sock );
    usr->setEvent ( MSG::JOIN );
}
void MainInstance::cGetLocationsInfo ( User* usr, Packet* pkt )
{
    usr->getObjectList ( "locations" )->commit();
}
void MainInstance::cStartLocation ( User* usr, Packet* pkt )
{
    IG_Int32 data = IG_Int32::decompress ( pkt );
    int location_id = data.iVal1;

    Object* target_location;
    DictObject *dict_target_location;
    ///sellecting appropriate location
    vector<DictObject>& dict_location_list = iDictManager->getLocation ( location_id );

    uint target_lvl = 0;
    for ( uint i = 0; i < dict_location_list.size(); ++i )
    {
        uint curr_lvl = dict_location_list[i].get ( "lvl" )->getInt();
        DictObject* dict_need_obj = dict_location_list[i].get ( "need_obj" )->getDictObject();
        if ( usr->isItemExist ( dict_need_obj->getId() ) )
        {
            if ( target_lvl < curr_lvl )
            {
                target_lvl = curr_lvl;
                dict_target_location = &dict_location_list[i];
            }
        }
    }
    ///cheking conditions
    if ( target_lvl == 0 )
        emitExeption ( ErrorExeption::UNLOCK_CONDITION_FAIL );

    int withdraw_obj_id = dict_target_location->get ( "withdraw_obj" )->getDictObject()->getId();
    if ( !usr->isItemExist ( withdraw_obj_id ) )
        emitExeption ( ErrorExeption::UNLOCK_CONDITION_FAIL );

    ///performing command
    ObjectList* location_list = usr->getObjectList ( "locations" );
    location_list->clear();
    Object new_loc = Object::createLocation ( location_id );
    location_list->add ( location_id, new_loc );
    target_location = location_list->get ( location_id );

    int dict_max_duration = dict_target_location->get ( "max_duration" )->getInt();
    int curr_time = iStorage->getCurrentTime();
    int &master_end_time = target_location->get ( "master_end_time" )->getInt();
    if ( master_end_time > curr_time )
        emitExeption ( ErrorExeption::LOCATION_ALLREADY_IN_WORK );
    ///performing command
    usr->withdrawItem ( withdraw_obj_id );
    target_location->get ( "lvl_on_work" )->getInt() = target_lvl;
    master_end_time = curr_time + dict_max_duration;

    usr->setEvent ( MSG::LOCATION_START );
}
void MainInstance::cFinishLocation ( User* usr, Packet* pkt )
{
    IG_2Int32 data = IG_2Int32::decompress ( pkt );
    int location_id = data.iVal1;
    int win = data.iVal2;

    ///cheking conditions
    ObjectList* location_list = usr->getObjectList ( "locations" );
    Object* loc = location_list->get ( location_id );

    DictObject* dict_location = NULL;
    ///performing command
    vector<DictObject>& dict_location_list = iDictManager->getLocation ( location_id );
    for ( uint i = 0; i < dict_location_list.size(); ++i )
    {
        if ( dict_location_list[i].get ( "lvl" )->getInt() == loc->get ( "lvl_on_work" )->getInt() )
            dict_location = &dict_location_list[i];
    }

    if ( dict_location == NULL )
        emitExeption ( ErrorExeption::LOCATION_ALLREADY_IN_WORK );

    int &lvl_on_work = loc->get ( "lvl_on_work" )->getInt();
    int &master_end_time = loc->get ( "master_end_time" )->getInt();
    if ( lvl_on_work > 0 )
    {
        if ( win == false )
        {
            DictObject *dict_lose_reward_obj = dict_location->get ( "lose_reward_obj" )->getDictObject();
            usr->addItem ( dict_lose_reward_obj->getId() );
            usr->setEvent ( MSG::LOCATION_LOSE );
        }
        else
        {
            DictObject *dict_win_reward_obj = dict_location->get ( "win_reward_obj" )->getDictObject();
            usr->addItem ( dict_win_reward_obj->getId() );
            usr->setEvent ( MSG::LOCATION_WIN );
        }
    }
    lvl_on_work = 0;
    master_end_time = 0;
    location_list->commit();
}
void MainInstance::cKickBoss ( User* usr, Packet* pkt )
{
    IG_2Int32 data = IG_2Int32::decompress ( pkt );
    int boss_id = data.iVal2;
    int kick_id = data.iVal1;
    BossFightControl *boss = BossFightControl::getControl ( usr, boss_id );
    boss->kick ( kick_id );
    usr->setEvent ( MSG::BOSS_IN_FIGHT );
}
void MainInstance::cGetBossUpdate ( User* usr, Packet* pkt )
{
    BossFightControl *boss = BossFightControl::getControl ( usr );
    if ( boss == NULL )
    {
        usr->setEvent ( MSG::BOSS_NOT_IN_FIGHT );
    }
    else
    {
        boss->update();
	usr->setEvent ( boss->getStatus() );
    }
}
void MainInstance::cExchange ( User* usr, Packet* pkt )
{
    IG_Int32 data = IG_Int32::decompress ( pkt );
    int slot_id = data.iVal1;

    DictExchange &dict_exch = iDictManager->getExchangeSlot ( slot_id );

    if ( !usr->isItemExist ( dict_exch._withdraw_obj->getId(), dict_exch._withdraw_obj_count ) )
        emitExeption ( ErrorExeption::NOT_ENOUGHT_ITEMS );

    usr->withdrawItem ( dict_exch._withdraw_obj->getId(), dict_exch._withdraw_obj_count );
    usr->addItem ( dict_exch._give_obj->getId(), dict_exch._give_obj_count );
    usr->setEvent ( MSG::EXCHANGE_SUCCESS );
}
void MainInstance::cReqColl ( User* usr, Packet* pkt )
{
    IG_STR data = IG_STR::decompress ( pkt );
    string collections = data.str;

    JSONValue *jval = JSON::parse ( collections.c_str() );

    if ( jval == NULL || !jval->isArray() )
    {
        usr->setEvent ( MSG::REQ_COLL_FAIL );
        return;
    }
    JSONArray jarr = jval->asArray();
    if ( jarr.size() > 5 )
    {
        usr->setEvent ( MSG::REQ_COLL_FAIL );
        return;
    }
    ///CHECKING IF REALY ALL ELLEMENTS IS COLLECTION_PARTS
    for ( uint i = 0; i < jarr.size(); ++i )
    {
        if ( !jarr[i]->isObject() )
        {
            usr->setEvent ( MSG::REQ_COLL_FAIL );
            return;
        }
        JSONObject jobj = jarr[i]->asObject();
        auto jit = jobj.find ( "id" );

        if ( jit == jobj.end() )
        {
            usr->setEvent ( MSG::REQ_COLL_FAIL );
            return;
        }
        if ( !jit->second->isNumber() )
        {
            usr->setEvent ( MSG::REQ_COLL_FAIL );
            return;
        }
        int collection_id = jit->second->asNumber();
        DictObject *dict_obj = iDictManager->getObject ( collection_id );
        if ( dict_obj->type != COLLECTION_PART )
        {
            usr->setEvent ( MSG::REQ_COLL_FAIL );
            return;
        }
    }
    ObjectList *obj_list = usr->getObjectList ( "req_collections" );
    obj_list->deserialize ( collections );
    usr->setEvent ( MSG::REQ_COLL_SUCCESS );
}
