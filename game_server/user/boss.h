#ifndef BOSS_H
#define BOSS_H

#include "dict_object.h"
#include "common.h"
#include "user.h"

struct Kick
{
    Kick(int uid, int time, int damage) : _time(time),  _uid(uid), _damage(damage)
    {}
    int _time;
    int _uid;
    int _damage;
};

class BossFightControl
{
public:
    enum DAMAGE_TYPE { PURE, PERCENTAGE };
    enum STATUS { NOT_IN_FIGHT = MSG::BOSS_NOT_IN_FIGHT, IN_FIGHT = MSG::BOSS_IN_FIGHT, WAITING_FOR_WIN_REWARD = MSG::BOSS_WIN_REWARD, WAITING_FOR_LOSE_REWARD = MSG::BOSS_LOSE_REWARD };
    static BossFightControl* getControl(User *uid, int boss_id);
    static BossFightControl* getControl(User *uid);
    void kick(int item_id);
    STATUS getStatus(){ return _status; };
    
    void beginFight();
    void endFight();
    void update();
    
    virtual ~BossFightControl(){};
private:
    BossFightControl(){};

    int getItemDamage(int item_id);
    int getItemCooldown(int item_id);
    int getItemDamageType(int item_id);

    void deserialize();
    void serializeClient();
    void serializeSql();

    void deserializeKickLog(string kick_log_str);
    string serializeKickLogClient();
    string serializeKickLogSql();

    void cbFriendWithdrawHp(int uid, int damage);///CALL BACK. CALLED WHEN FRIEND KICKS HIS BOSS.
    void cbFriendFightBegin(BossFightControl *friend_boss);///CALL BACK. CALLED WHEN NEW FRIEND BOSS FIGHT STARTED.
    void cbFriendFightEnd(BossFightControl *friend_boss);///CALL BACK. CALLED WHEN NEW FRIEND BOSS FIGHT END.
    
    void withdrawHp(int damage);
    void withdrawFriendsHp(int damage);
    
    void checkBossState();
    
    int _user_id;
    int _boss_id;
    int _current_hp;
    int _start_time;
    int _end_time;
    int _cooldown_time;
    vector<Kick> _kick_log;

    STATUS _status;
    
    User *_owner;

    set<BossFightControl*> _friends_bosses;
    Mutex _boss_lock;

    static associative_container<int, BossFightControl*> _boss_list;///map<uid, BossFightControl>
    static Mutex _boss_list_lock;

    DictObject *dict;
};

#endif // BOSS_H
