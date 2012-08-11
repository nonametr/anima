#include "user.h"
#include "command_structs.h"
#include "json.h"
#include "json_value.h"
#include "storage.h"
#include "dict_object.h"
#include "exeption.h"
#include "random.h"

User::User() : joined ( false )
{

}
User::~User()
{

}
void User::join ( Socket *sock )
{
    _sock 	= sock;
    joined 	= true;

    for ( auto it = _values.begin(); it != _values.end(); ++it )
    {
        it->second.commit();
    }
    for ( auto it = _object_lists.begin(); it != _object_lists.end(); ++it )
    {
        it->second.commit();
    }
}
bool User::isItemExist ( int item_id, int count )
{
    DictObject *dict_obj = iDictManager->getObject ( item_id );

    if ( dict_obj->type == ITEM_PACK )
    {
        auto item_list = iDictManager->getDictPack ( item_id );
        for ( uint i = 0; i < item_list.size(); ++i )
        {
            if ( isItemExist ( item_list[i]._in_pack_obj->getId() ) == false )
                return false;
        }
        return true;
    }

    traceerr("list = %s", object_types_str[dict_obj->type].c_str() );
    ObjectList *item_list = getObjectList ( object_types_str[dict_obj->type].c_str() );
    if ( item_list->isExist ( item_id, count ) )
        return true;
    else
        return false;
}
void User::addItem ( int item_id, int count )
{
    int current_count = 0, new_count;
    DictObject *dict_obj = iDictManager->getObject ( item_id );
    if ( dict_obj->type == ITEM_PACK )
    {
        auto item_list = iDictManager->getDictPack ( item_id );
        for ( uint i = 0; i < item_list.size(); ++i )
        {
            if ( item_list[i]._chance >= 10000 )
            {
                addItem ( item_list[i]._in_pack_obj->getId(), item_list[i]._count );
            }
            else
            {
                uint rand = iRandom->Rand ( 0, MAX_PERCENT );
                if ( item_list[i]._chance >= rand )
                {
                    addItem ( item_list[i]._in_pack_obj->getId(), item_list[i]._count );
                }
            }
        }
        return;
    }
    ObjectList *item_list = getObjectList ( object_types_str[dict_obj->type].c_str() );
    item_list->commit();
    if ( item_list->isExist ( item_id ) )
    {
        Object *item = item_list->get ( item_id );
        current_count = item->get ( "count" )->getInt();
        new_count = current_count + count;
        item->get ( "count" )->getInt() = new_count;
    }
    else
    {
        new_count = current_count + count;
        item_list->add ( item_id, Object::createItem ( item_id ) );
        item_list->get ( item_id )->get ( "count" )->getInt() = new_count;
    }
    vector<DictGive> *dict_give = iDictManager->getDictGive ( item_id );
    if ( dict_give == NULL )
        return;
    for ( uint i = 0; i < dict_give->size(); ++i )
    {
        if ( dict_give->at ( i )._if_obj_count > current_count &&  dict_give->at ( i )._if_obj_count < new_count )
        {
            addItem ( dict_give->at ( i )._give_obj->getId(), dict_give->at ( i )._give_count );
        }
    }
}
void User::withdrawItem ( int item_id, int count )
{
    DictObject *dict_obj = iDictManager->getObject ( item_id );

    if ( dict_obj->type == ITEM_PACK )
    {
        auto item_list = iDictManager->getDictPack ( item_id );
        for ( uint i = 0; i < item_list.size(); ++i )
        {
            withdrawItem ( item_list[i]._in_pack_obj->getId(), item_list[i]._count );
        }
        return;
    }

    ObjectList *item_list = getObjectList ( object_types_str[dict_obj->type].c_str() );
    item_list->commit();
    if ( item_list->isExist ( item_id, count ) )
    {
        item_list->get ( item_id )->get ( "count" )->getInt() -= count;
    }
}
///--------------SETTERS----------------
void User::setEvent ( int msg_id )
{
    ObjectList *item_list = getObjectList ( "events" );
    item_list->commit();
    item_list->clear();
    item_list->add ( msg_id, Object::createMessage ( msg_id ) );
}
void User::set ( string key, Value value )
{
    if ( joined )
    {
        value.commit();
    }
    _values[key] = value;
}
void User::setObjectList ( string key, string value )
{
    ObjectList obj_list;
    obj_list.deserialize ( value );
    _object_lists[key] = obj_list;
}
void User::setPrivateObjectList ( string key, string value )
{
    ObjectList obj_list;
    obj_list.deserialize ( value );
    _private_object_lists[key] = obj_list;
}
///-------------GETTERS-----------------
Value* User::get ( string key )
{
    auto it = _values.find ( key );
    if ( it != _values.end() )
    {
        return &it->second;
    }
    emitExeption ( ErrorExeption::VALUE_NOT_FOUND );
    exit ( 0 );
}
ObjectList* User::getObjectList ( string key )
{
    auto it = _object_lists.find ( key );
    if ( it != _object_lists.end() )
    {
        return &it->second;
    }
    emitExeption ( ErrorExeption::OBJECT_NOT_FOUND );
    exit ( 0 );
}
ObjectList* User::getPrivateObjectList ( string key )
{
    auto it = _private_object_lists.find ( key );
    if ( it != _private_object_lists.end() )
    {
        return &it->second;
    }
    emitExeption ( ErrorExeption::PRIVATE_OBJECT_NOT_FOUND );
    exit ( 0 );
}
///-----------CLIENT_SYNC---------------
void User::updateClient()
{
    JSONValue *val;
    JSONObject json_obj;
    for ( auto it = _values.begin(); it != _values.end(); ++it )
    {
        if ( it->second.needCommit() )
        {
            switch ( it->second.type )
            {
            case Value::STRING:
                json_obj[it->first] =  new JSONValue ( it->second.getString() );
                break;
            case Value::INT:
                json_obj[it->first] = new JSONValue ( intToString ( it->second.getInt() ) );
                break;
            default:
                break;
            }
            it->second.commitDone();
        }
    }
    for ( auto it = _object_lists.begin(); it != _object_lists.end(); ++it )
    {
        if ( it->second.needCommit() )
        {
            json_obj[it->first] = JSON::parse ( it->second.serialize()->stringify().c_str() );
            it->second.commitDone();
        }
    }
    _object_lists["events"].clear();
    val = new JSONValue ( json_obj );
    string json = val->stringify();
    traceerr ( "json = %s", json.c_str() );
    Packet client_update_pkt = OG_USER_JSON::create ( json );
    _sock->send ( &client_update_pkt );
}
void User::updateSql()
{
    string sql ( UPDATE_HEADER );
    for ( auto it = _values.begin(); it != _values.end(); ++it )
    {
        if ( it->second.sqlNeedCommit() )
        {
            sql += it->first + "=";
            switch ( it->second.type )
            {
            case Value::STRING:
                sql += "\"" + it->second.getString() + "\"";
                break;
            case Value::INT:
                sql += "\"" + intToString ( it->second.getInt() ) + "\"";
                break;
            }
            sql += ",";
            it->second.sqlCommitDone();
        }
    }
    for ( auto it = _object_lists.begin(); it != _object_lists.end(); ++it )
    {
        if ( it->second.sqlNeedCommit() )
        {
            sql += it->first + "=";
            sql += "\"" + it->second.serialize()->stringify() + "\"";
            sql += ",";
            it->second.sqlCommitDone();
        }
    }
    for ( auto it = _private_object_lists.begin(); it != _private_object_lists.end(); ++it )
    {
        if ( it->second.sqlNeedCommit() )
        {
            sql += it->first + "=";
            sql += "\"" + it->second.serialize()->stringify() + "\"";
            sql += ",";
            it->second.sqlCommitDone();
        }
    }

    sql += "WHERE user_data.uid = " + intToString ( this->get ( "uid" )->getInt() );
//     iDBManager->getDatabase ( this->get ( "db_id" )->getInt() )->executeNA ( sql.c_str() );
    traceerr ( "sql_save=%s", sql.c_str() );
}

