#ifndef DICT_MANAGER_H
#define DICT_MANAGER_H


#include "common.h"
#include "database_manager.h"

class User;
class DictObject;

#define TEMPLATE_USER_ID 0

struct DictGive
{
    DictGive ( DictObject *obj, DictObject *give_obj, int if_obj_count, int give_count ) : _obj ( obj ), _give_obj ( give_obj ),  _if_obj_count ( if_obj_count
),
        _give_count ( give_count )
    {};
    DictObject *_obj;
    DictObject *_give_obj;
    int _if_obj_count;
    int _give_count;
};
struct DictPack
{
    DictPack ( DictObject *obj, DictObject *in_pack_obj, uint count, uint chance ) :_obj ( obj ), _in_pack_obj ( in_pack_obj ), _count ( count ), _chance (
chance )
    {};
    DictObject *_obj;
    DictObject *_in_pack_obj;
    uint _count;
    uint _chance;
};
struct DictExchange
{
    DictExchange() {};
    DictExchange ( DictObject *give_obj, uint give_obj_count, DictObject *withdraw_obj, uint withdraw_obj_count )
        : _give_obj ( give_obj ), _give_obj_count ( give_obj_count ), _withdraw_obj ( withdraw_obj ), _withdraw_obj_count ( withdraw_obj_count )
    {};
    DictObject *_give_obj;
    uint _give_obj_count;
    DictObject *_withdraw_obj;
    uint _withdraw_obj_count;
};

class DictManager : public Singleton<DictManager>
{
public:
    DictManager();
    virtual ~DictManager();
    
    User *cloneTemplateUser();
	
    vector<DictGive>* getDictGive ( int id );
    vector<DictPack>& getDictPack ( int id );
    DictObject* getObject ( uint id );
    vector<DictObject>& getLocation ( uint id );
    DictExchange &getExchangeSlot(uint slot_id);
    string& getMsg ( uint id );
    DictObject* getNamedObject ( string name );
private:
    void loadDict();
    void loadGive();
    void loadPack();
    void loadLocation();
    void loadMsg();
    void loadExchange();
    void loadTemplateUser();

    associative_container<int, string > _dict_msg;
    associative_container<int, vector<DictGive> > _dict_give;///some kinda multimap
    associative_container<int, DictExchange > _dict_exchange;
    associative_container<int, vector<DictPack> > _dict_pack;
    associative_container<int, vector<DictObject> > _dict_location;

    associative_container<int, DictObject* > _dict_objects;
    associative_container<string, DictObject* > _dict_named_objects;

    User *template_user;
};

#define iDictManager DictManager::getSingletonPtr()
#endif // DICT_MANAGER_H
