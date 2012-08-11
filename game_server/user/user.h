#ifndef USER_H
#define USER_H

#include "user_interface.h"
#include "common.h"
#include "value.h"
#include "socket.h"
#include "object.h"
#include "login_socket.h"

#define UPDATE_HEADER "UPDATE user_data \
LEFT JOIN user_data_objects ON user_data.uid = user_data_object.uid \
LEFT JOIN user_data_private ON user_data.uid = user_data_private.uid \
LEFT JOIN user_rating_data ON user_data.uid = user_rating_data.uid \
SET "

class User //: public UserInterface
{
    friend class LoginSocket;
public:
    User();
    virtual ~User();
    void onSessionClose() {};
    void join ( Socket *sock );
///-------INTERFACE REALIZATION---------
///--------------SETTERS----------------
    void set ( string key, Value value );
    void setObjectList ( string key, string value );
    void setPrivateObjectList ( string key, string value );
///-------------GETTERS-----------------
    Value* get ( string key );
    ObjectList* getObjectList ( string key );
    ObjectList* getPrivateObjectList ( string key );

    void exchange(int slot_id);
    bool isItemExist ( int item_id, int count = 1 );
    void withdrawItem ( int item_id, int count = 1 );
    void addItem ( int item_id, int count = 1 );
    void setEvent ( int msg_id );
    void lock()
    {
        _lock.lock();
    }
    void unlock()
    {
        _lock.unlock();
    }
    void updateClient();
    void updateSql();
private:
    associative_container< string, Value > _values;//map< param_name, param_value>
    associative_container< string, ObjectList > _object_lists;
    associative_container< string, ObjectList > _private_object_lists;
    bool joined;
    Mutex _lock;
    Socket *_sock;
};

#endif // USER_H
