#include "dict_manager.h"
#include "value.h"
#include "dict_object.h"
#include "storage.h"
#include "user.h"

initialiseSingleton ( DictManager );

DictManager::DictManager()
{
    loadMsg();
    loadDict();
    loadGive();
    loadPack();
    loadLocation();
}
DictManager::~DictManager()
{

}
DictObject* DictManager::getNamedObject ( string name )
{
//     shrinkSpaces(name);
    auto it = _dict_named_objects.find ( name );
    if ( it != _dict_named_objects.end() )
        return it->second;
    emitExeption ( ErrorExeption::NAME_NOT_FOUND_IN_DICT );
    exit ( 0 );
}
DictObject* DictManager::getObject ( uint id )
{
    auto it = _dict_objects.find ( id );
    if ( it != _dict_objects.end() )
        return it->second;
    emitExeption ( ErrorExeption::ID_NOT_FOUND_IN_DICT );
    exit ( 0 );
}
vector<DictGive>* DictManager::getDictGive ( int id )
{
    auto it = _dict_give.find ( id );
    if ( it != _dict_give.end() )
        return &it->second;
    else return NULL;
}
vector<DictObject>& DictManager::getLocation ( uint id )
{
    auto it = _dict_location.find ( id );
    if ( it != _dict_location.end() )
        return it->second;
    emitExeption ( ErrorExeption::ID_NOT_FOUND_IN_DICT );
    exit ( 0 );
}
DictExchange &DictManager::getExchangeSlot ( uint slot_id )
{
    auto it = _dict_exchange.find ( slot_id );
    if ( it != _dict_exchange.end() )
        return it->second;
    emitExeption ( ErrorExeption::ID_NOT_FOUND_IN_DICT );
    exit ( 0 );
}
vector<DictPack>& DictManager::getDictPack ( int id )
{
    auto it = _dict_pack.find ( id );
    if ( it != _dict_pack.end() )
        return it->second;
    emitExeption ( ErrorExeption::ID_NOT_FOUND_IN_DICT );
    exit ( 0 );
}
string& DictManager::getMsg ( uint id )
{
    auto it = _dict_msg.find ( id );
    if ( it != _dict_msg.end() )
        return it->second;
    emitExeption ( ErrorExeption::ID_NOT_FOUND_IN_DICT );
    exit ( 0 );
}
void DictManager::loadTemplateUser()
{
    template_user = iStorage->loadUser ( TEMPLATE_USER_ID );
}
User *DictManager::cloneTemplateUser()
{
    User *usr = new User;
    *usr = *template_user;
    return usr;
}
void DictManager::loadExchange()
{
    Field *field;
    shared_ptr<QueryResult> qres_dict_exchange ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_EXCHANGE ) );
    if ( qres_dict_exchange.get() == NULL )
    {
        traceerr ( "%s", "Error! Dictionary give corrupted!" );
        exit ( 0 );
    }
    do
    {
        field = qres_dict_exchange->fetch();
        DictObject *give_obj = getNamedObject ( field[0].getString() );
        DictObject *withdraw_obj = getNamedObject ( field[2].getString() );
        uint give_count = field[1].getUInt32();
        uint withdraw_count = field[3].getUInt32();
        uint slot_id = field[4].getUInt32();
        _dict_exchange[slot_id] = DictExchange ( give_obj, give_count, withdraw_obj, withdraw_count );
    }
    while ( qres_dict_exchange->nextRow() );
}
void DictManager::loadMsg()
{
    Field *field;
    shared_ptr<QueryResult> qres_dict_msg ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_MSG ) );
    if ( qres_dict_msg.get() == NULL )
    {
        traceerr ( "%s", "Error! Dictionary give corrupted!" );
        exit ( 0 );
    }
    do
    {
        field = qres_dict_msg->fetch();
        uint id = field[0].getUInt32();
        string msg_eng = field[2].getString();
        _dict_msg[id] = msg_eng;
    }
    while ( qres_dict_msg->nextRow() );
}
void DictManager::loadLocation()
{
    Field *field;
    shared_ptr<QueryResult> qres_dict_location ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_LOCATION ) );
    if ( qres_dict_location.get() == NULL )
    {
        traceerr ( "%s", "Error! Dictionary give corrupted!" );
        exit ( 0 );
    }
    do
    {
        DictObject obj;
        field = qres_dict_location->fetch();
        DictObject *owner = getNamedObject ( field[0].getString() );
        obj._id = owner->getId();
        for ( uint32 i = 0; i < qres_dict_location->getFieldCount(); ++i )
        {
            switch ( field[i].getType() )
            {
            case MYSQL_TYPE_DECIMAL:
            case MYSQL_TYPE_TINY:
            case MYSQL_TYPE_SHORT:
            case MYSQL_TYPE_LONG:
            case MYSQL_TYPE_INT24:
                obj._values[field[i].getFieldName()] = ( int ) field[i].getUInt32();
                break;
            case MYSQL_TYPE_VARCHAR:
            case MYSQL_TYPE_VAR_STRING:
            case MYSQL_TYPE_STRING:
                obj._values[field[i].getFieldName()] = field[i].getString();
                break;
            default:
                break;
            }
        }
        _dict_location[obj.getId()].push_back ( obj );
    }
    while ( qres_dict_location->nextRow() );
}
void DictManager::loadPack()
{
    Field *field;
    shared_ptr<QueryResult> qres_dict_pack ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_PACK ) );
    if ( qres_dict_pack.get() == NULL )
    {
        traceerr ( "%s", "Error! Dictionary give corrupted!" );
        exit ( 0 );
    }
    do
    {
        uint chance = 10000;
        field = qres_dict_pack->fetch();
        DictObject *object = getNamedObject ( field[0].getString() );
        DictObject *in_pack_obj = getNamedObject ( field[1].getString() );
        shared_ptr<QueryResult> qres_dict_drop_chance ( iDBManager->getSSDatabase()->query ( DB_GET_DICT_DROP_CHANCE__OBJ_IN_PACK, field[0].getString(),
                field[1].getString() ) );
        if ( qres_dict_drop_chance.get() != NULL )
        {
            chance = qres_dict_drop_chance->fetch() [0].getUInt32();
        }
        int count = field[2].getUInt32();
        _dict_pack[object->getId()].push_back ( DictPack ( object, in_pack_obj, count, chance ) );
    }
    while ( qres_dict_pack->nextRow() );
}
void DictManager::loadGive()
{
    Field *field;
    shared_ptr<QueryResult> qres_dict_give ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_GIVE ) );
    if ( qres_dict_give.get() == NULL )
    {
        traceerr ( "%s", "Error! Dictionary give corrupted!" );
        exit ( 0 );
    }
    do
    {
        field = qres_dict_give->fetch();
        DictObject *object = getNamedObject ( field[0].getString() );
        DictObject *give = getNamedObject ( field[2].getString() );
        _dict_give[object->getId()].push_back ( DictGive ( object, give, field[1].getUInt32(), field[3].getUInt32() ) );
    }
    while ( qres_dict_give->nextRow() );
}
void DictManager::loadDict()
{
    associative_container<string, string> type_table;
    Field *field;

    shared_ptr<QueryResult> qres_dict_object_types ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_OBJECT_TYPES ) );
    shared_ptr<QueryResult> qres_dict_object ( iDBManager->getSSDatabase()->queryNA ( DB_GET_DICT_OBJECT ) );
    if ( qres_dict_object_types.get() == NULL || qres_dict_object.get() == NULL )
    {
        traceerr ( "%s", "Error! Dictionary corrupted!" );
        exit ( 0 );
    }
    do
    {
        field = qres_dict_object_types->fetch();
        type_table[field[0].getString()] = field[1].getString();
    }
    while ( qres_dict_object_types->nextRow() );

    do
    {
        DictObject* obj = new DictObject;
        field 		= qres_dict_object->fetch();
        obj->getId() 	= field[0].getUInt32();
        obj->getName() 	= field[1].getString();
        string type 	= field[5].getString();
        if ( type == "LOCATION" )
            obj->type = LOCATION;
        else if ( type == "GLOBAL" )
            obj->type = GLOBAL;
        else if ( type == "BOSS" )
            obj->type = BOSS;
        else if ( type == "BOSS_STRIKE" )
            obj->type = BOSS_STRIKE;
        else if ( type == "ITEM" )
            obj->type = ITEM;
        else if ( type == "ITEM_PACK" )
            obj->type = ITEM_PACK;
        else if ( type == "BULLETS" )
            obj->type = BULLETS;
        else if ( type == "EXP" )
            obj->type = EXP;
        else if ( type == "GOLD" )
            obj->type = GOLD;
        else if ( type == "MONEY" )
            obj->type = MONEY;
        else if ( type == "LVL" )
            obj->type = LVL;
        else if ( type == "ENERGY" )
            obj->type = ENERGY;
        else if ( type == "COLLECTION" )
            obj->type = COLLECTION;
        else if ( type == "COLLECTION_PART" )
            obj->type = COLLECTION_PART;
        else
        {
            traceerr ( "Loading dict fail, cose object type unrecognized! type = %s", type.c_str() );
            exit ( 1 );
        }
        if ( type_table[type] != "global" )
        {
            if ( type_table.find ( type ) == type_table.end() )
            {
                traceerr ( "Error! No such type defined => %s!", type.c_str() );
                exit ( 0 );
            }
            shared_ptr<QueryResult> qres_dict_details ( iDBManager->getSSDatabase()->query ( DB_GET_OBJECT_INFO__TABLE_OBJECT_NAME, type_table[type].c_str(),
                    obj->getName().c_str() ) );
            if ( qres_dict_details.get() == NULL )
            {
                traceerr ( "Error! No data found for object => %s!", obj->getName().c_str() );
                exit ( 0 );
            }
            field = qres_dict_details->fetch();
            for ( uint32 i = 0; i < qres_dict_details->getFieldCount(); ++i )
            {
                switch ( field[i].getType() )
                {
                case MYSQL_TYPE_DECIMAL:
                case MYSQL_TYPE_TINY:
                case MYSQL_TYPE_SHORT:
                case MYSQL_TYPE_LONG:
                case MYSQL_TYPE_NULL:
                case MYSQL_TYPE_TIMESTAMP:
                case MYSQL_TYPE_LONGLONG:
                case MYSQL_TYPE_INT24:
                case MYSQL_TYPE_FLOAT:
                case MYSQL_TYPE_DOUBLE:
                    obj->_values[field[i].getFieldName()] = ( int ) field[i].getUInt32();
                    break;
                case MYSQL_TYPE_DATE:
                case MYSQL_TYPE_TIME:
                case MYSQL_TYPE_DATETIME:
                case MYSQL_TYPE_YEAR:
                case MYSQL_TYPE_NEWDATE:
                case MYSQL_TYPE_VARCHAR:
                case MYSQL_TYPE_BIT:
                case MYSQL_TYPE_NEWDECIMAL:
                case MYSQL_TYPE_ENUM:
                case MYSQL_TYPE_SET:
                case MYSQL_TYPE_TINY_BLOB:
                case MYSQL_TYPE_MEDIUM_BLOB:
                case MYSQL_TYPE_LONG_BLOB:
                case MYSQL_TYPE_BLOB:
                case MYSQL_TYPE_VAR_STRING:
                case MYSQL_TYPE_STRING:
                case MYSQL_TYPE_GEOMETRY:
                    obj->_values[field[i].getFieldName()] = field[i].getString();
                    break;
                default:
                    break;
                }
            }
        }
        _dict_named_objects[obj->getName()] = obj;
        _dict_objects[obj->getId()] = obj;
    }
    while ( qres_dict_object->nextRow() );
}

