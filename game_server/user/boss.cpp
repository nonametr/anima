#include "boss.h"
#include "exeption.h"
#include <stdio.h>
#include "storage.h"
#include "common.h"

Mutex BossFightControl::_boss_list_lock = Mutex();
associative_container<int, BossFightControl*> BossFightControl::_boss_list = associative_container<int, BossFightControl*>();

BossFightControl *BossFightControl::getControl ( User *usr, int boss_id )
{
    _boss_list_lock.lock();
    auto it = _boss_list.find ( usr->get ( "uid" )->getInt() );
    if ( it != _boss_list.end() )
    {
        if ( it->second->_boss_id == boss_id )
        {
            _boss_list_lock.unlock();
            it->second->_owner = usr;
            return it->second;
        }
        else
        {
            _boss_list_lock.unlock();
            emitExeption ( ErrorExeption::OTHER_BOSS_FIGHT_IN_PROGRESS );
        }
    }
    else
    {
        BossFightControl *boss = new BossFightControl;
        boss->_owner = usr;
        boss->_boss_id = boss_id;
        return boss;
    }
    _boss_list_lock.unlock();
    return NULL;
}
BossFightControl *BossFightControl::getControl ( User *usr )
{
    _boss_list_lock.lock();
    auto it = _boss_list.find ( usr->get ( "uid" )->getInt() );
    if ( it != _boss_list.end() )
    {
        _boss_list_lock.unlock();
        it->second->_owner = usr;
        return it->second;
    }
    _boss_list_lock.unlock();
    return NULL;
}
void BossFightControl::beginFight()
{
    if ( _status != NOT_IN_FIGHT )
        emitExeption ( ErrorExeption::OTHER_BOSS_FIGHT_IN_PROGRESS );
    vector<int> friends;
    ObjectList *friend_list = _owner->getObjectList ( "app_friends" );

    _status = IN_FIGHT;
    for ( auto it = friend_list->begin(); it != friend_list->end(); ++it )
    {
        friends.push_back ( it->second.get ( "id" )->getInt() );
    }
    _boss_list_lock.lock();
    for ( uint i = 0; i < friends.size(); ++i )
    {

        auto it = _boss_list.find ( friends[i] );
        if ( it != _boss_list.end() )
        {
            this->cbFriendFightBegin ( it->second );
            it->second->cbFriendFightBegin ( this );
        }
    }
    _boss_list[_user_id] = this;
    _boss_list_lock.unlock();
}
void BossFightControl::endFight()
{
    _boss_list_lock.lock();
    _boss_list.erase ( _user_id );
    _boss_lock.lock();
    for ( auto it = _friends_bosses.begin(); it != _friends_bosses.end(); ++it )
    {
        ( *it )->cbFriendFightEnd ( this );
    }
    _boss_lock.unlock();
    _boss_list_lock.unlock();
}
void BossFightControl::cbFriendFightEnd ( BossFightControl *friend_boss )
{
    _boss_lock.lock();
    _friends_bosses.erase ( friend_boss );
    _boss_lock.unlock();
}
void BossFightControl::cbFriendFightBegin ( BossFightControl *friend_boss )
{
    _boss_lock.lock();
    _friends_bosses.insert ( friend_boss );
    _boss_lock.unlock();
}
void BossFightControl::cbFriendWithdrawHp ( int friend_uid, int damage )
{
    _boss_lock.lock();
    _current_hp -= damage;
    _kick_log.push_back ( Kick ( friend_uid, iStorage->getCurrentTime(), damage ) );
    checkBossState();
    _boss_lock.unlock();
}
void BossFightControl::checkBossState()
{
    if ( _end_time <= iStorage->getCurrentTime() )
    {
        _status = WAITING_FOR_LOSE_REWARD;
        endFight();
    }
    if ( _current_hp <= 0 )
    {
        _status = WAITING_FOR_WIN_REWARD;
        endFight();
    }
}
void BossFightControl::kick ( int item_id )
{
    int damage = getItemDamage ( item_id );
    int cooldown = getItemCooldown ( item_id );
    int damage_type = getItemDamageType ( item_id );

    if ( cooldown == 0 )
    {
        if ( !_owner->isItemExist ( item_id ) )
            ErrorExeption ( ErrorExeption::BOSS_STRIKE_NO_ITEM, intToString ( __LINE__ ) +string ( " " ) + string ( __FUNCTION__ ) );
        else
            _owner->withdrawItem ( item_id );
    }
    _boss_lock.lock();
    if ( damage_type == PERCENTAGE )
        damage = ( int ) _current_hp * ( damage/100 );

    if ( cooldown > 0 )
    {
        if ( _cooldown_time - iStorage->getCurrentTime() > cooldown )
        {
            _boss_lock.unlock();
            _owner->setEvent ( MSG::BOSS_ON_COOLDOWN );
            return;
        }
        else
        {
            _cooldown_time += cooldown;
        }
    }
    _boss_lock.unlock();
    withdrawHp ( damage );

    if ( damage_type != PERCENTAGE )
        withdrawFriendsHp ( damage );
    serializeClient();
}
void BossFightControl::withdrawHp ( int damage )
{
    _boss_lock.lock();
    _current_hp -= damage;
    _kick_log.push_back ( Kick ( _user_id, iStorage->getCurrentTime(), damage ) );
    checkBossState();
    _boss_lock.unlock();
}
void BossFightControl::withdrawFriendsHp ( int damage )
{
    _boss_lock.lock();
    set<BossFightControl*> _friends_bosses_cpy = _friends_bosses;
    _boss_lock.unlock();
    for ( auto it = _friends_bosses_cpy.begin(); it != _friends_bosses_cpy.end(); ++it )
    {
        ( *it )->cbFriendWithdrawHp ( _user_id, damage );
    }
}
void BossFightControl::update()
{
    serializeClient();
}
int BossFightControl::getItemDamage ( int item_id )
{
    return iDictManager->getObject ( item_id )->get ( "damage" )->getInt();
}
int BossFightControl::getItemCooldown ( int item_id )
{
    return iDictManager->getObject ( item_id )->get ( "cooldown" )->getInt();
}
int BossFightControl::getItemDamageType ( int item_id )
{
    string dmg_type = iDictManager->getObject ( item_id )->get ( "damage_type" )->getString();
    if ( dmg_type == "PURE" )
        return PURE;
    else if ( dmg_type == "PERCENTAGE" )
        return PERCENTAGE;
    return PURE;
}
///------------------SERIALIZE/DESERIALIZE-----------------
void BossFightControl::deserialize()
{
    Object *boss = _owner->getPrivateObjectList ( "active_boss" )->get ( _boss_id );

    _start_time = boss->get ( "start_time" )->getInt();
    _end_time = boss->get ( "end_time" )->getInt();
    _current_hp = boss->get ( "current_hp" )->getInt();
    _cooldown_time = boss->get ( "cooldown_time" )->getInt();
    deserializeKickLog ( boss->get ( "kick_list" )->getString() );
    _status = ( STATUS ) boss->get ( "status" )->getInt();
}
void BossFightControl::serializeClient()
{
    Object *boss = _owner->getObjectList ( "active_boss" )->get ( _boss_id );

    boss->set ( "id", _boss_id );
    boss->set ( "start_time", _start_time );
    boss->set ( "end_time", _end_time );
    boss->set ( "current_hp", _current_hp );
    boss->set ( "cooldown_time", _cooldown_time );
    boss->set ( "kick_list", serializeKickLogClient() );
    boss->set ( "status", _status );

    _owner->getObjectList ( "active_boss" )->commit();
}
void BossFightControl::serializeSql()
{
    Object *boss_private = _owner->getPrivateObjectList ( "active_boss" )->get ( _boss_id );

    boss_private->set ( "id", _boss_id );
    boss_private->set ( "start_time", _start_time );
    boss_private->set ( "end_time", _end_time );
    boss_private->set ( "current_hp", _current_hp );
    boss_private->set ( "cooldown_time", _cooldown_time );
    boss_private->set ( "kick_list", serializeKickLogSql() );
    boss_private->set ( "status", _status );

    _owner->getPrivateObjectList ( "active_boss" )->commit();
}
void BossFightControl::deserializeKickLog ( string kick_log_str )
{
    int uid, time, damage;
    char *source_blob, *token, *prgrs;
    char sep[] = ",";
    source_blob  = ( char* ) kick_log_str.c_str();
    bool end = false;
    while ( !end )
    {
        for ( unsigned int i = 0; i < 3; i++ )
        {
            token = strtok_r ( source_blob, sep, &prgrs );
            if ( !token )
            {
                end = true;
                break;
            }
            sscanf ( token, "%u:%u:%u", &uid, &time, &damage );
            if ( source_blob )
                source_blob = NULL;
            _kick_log.push_back ( Kick ( uid, time, damage ) );
        }
    }
}
string BossFightControl::serializeKickLogSql()
{
    string result;
    char str_tmp[1024] = {"\0"};
    for ( uint i = 0; i < _kick_log.size(); ++i )
    {
        snprintf ( str_tmp, 1024, "%u:%u:%u", _kick_log[i]._uid, _kick_log[i]._time, _kick_log[i]._damage );
        result += str_tmp;
    }
    return result;
}

string BossFightControl::serializeKickLogClient()
{
    string result;
    uint size_max_8 = _kick_log.size() - 8 > 0 ? _kick_log.size() - 8: _kick_log.size();
    char str_tmp[1024] = {"\0"};
    for ( uint i = 0; i < size_max_8; ++i )
    {
        snprintf ( str_tmp, 1024, "%u:%u:%u", _kick_log[i]._uid, _kick_log[i]._time, _kick_log[i]._damage );
        result += str_tmp;
    }
    return result;
}
