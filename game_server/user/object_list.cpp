#include "object_list.h"
#include "value.h"
#include "json.h"
#include "json_value.h"
#include "exeption.h"

void ObjectList::add ( int id, Object obj )
{
    this->commit();
    _object_list[id] = obj;
}
void ObjectList::erase ( int id )
{
    this->commit();
    _object_list.erase ( id );
}
bool ObjectList::isExist ( int id, int count )
{
    auto it = _object_list.find ( id );
    if ( it != _object_list.end() )
    {
        if ( count >0 )
        {
            if ( count <= it->second.get ( "count" )->getInt() )
            {
                return true;
            }
            else
                return false;
        }
        else
            return true;
    }
    else
    {
        return false;
    }
}
Object* ObjectList::get ( int id )
{
    auto it = _object_list.find ( id );
    if ( it != _object_list.end() )
    {
        return &it->second;
    }
    ErrorExeption ( ErrorExeption::ID_NOT_FOUND_IN_OBJECT_LIST, intToString ( __LINE__ ) +string ( " " ) + string ( __FUNCTION__ ) );
    exit ( 0 );
}
void ObjectList::deserialize ( string init_str )
{
    _serialized_str = init_str;
    _deserializeObjectList();
}

void ObjectList::_deserializeObjectList()
{
    JSONValue *val = JSON::parse ( _serialized_str.c_str() );
    if ( !val )
        return;

    JSONArray js_arr = val->asArray();
    for ( uint i = 0; i < js_arr.size(); ++i )
    {
        JSONObject js_obj = js_arr[i]->asObject();
        if ( js_obj.find ( "id" ) == js_obj.end() )
            ErrorExeption ( ErrorExeption::DESERIALIZATION_ERROR, intToString ( __LINE__ ) +string ( " " ) + string ( __FUNCTION__ ) );
        int id = ( int ) js_obj["id"]->asNumber();
        Object obj = Object::createEmpty ( id );
        for ( auto it = js_obj.begin(); it != js_obj.end(); ++it )
        {
            if ( it->second->isNumber() )
            {
                obj.set ( it->first, it->second->asNumber() );
                continue;
            }
            if ( it->second->isString() )
            {
                obj.set ( it->first, it->second->getString() );
                continue;
            }
        }
        _object_list[id] = obj;
    }
    delete val;
}
void ObjectList::_serializeObjectList()
{
    string json;
    JSONArray js_arr;
    for ( auto it = _object_list.begin(); it != _object_list.end(); ++it )
    {
        JSONObject js_obj;
        for ( auto val_it = it->second.getBeginIterator(); val_it != it->second.getEndIterator(); ++val_it )
        {
            switch ( val_it->second.type )
            {
            case Value::STRING:
                js_obj[val_it->first] = new JSONValue ( ( string ) val_it->second.getString() );
                break;
            case Value::INT:
                js_obj[val_it->first] = new JSONValue ( (double)val_it->second.getInt() );
                break;
            default:
                break;
            }
        }
        js_arr.push_back ( new JSONValue ( js_obj ) );
    }
    _serialized_obj = JSONValue( js_arr );
}
JSONValue* ObjectList::serialize()
{
    _serializeObjectList();
    return &_serialized_obj;
}
void ObjectList::clear()
{
    this->commit();
    _object_list.clear();
}
