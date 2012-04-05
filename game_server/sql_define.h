#ifndef SQL_DEFINE_H
#define SQL_DEFINE_H

#define DB_GET_DESC "SELECT db_id, name, ip, port, user, password, charset FROM db_desc WHERE active = 1"

#define DB_GET_COUNT "SELECT MAX(db_id)+1 FROM db_desc WHERE active = 1"

#define DB_LOCK_SQL__PID_WORK_PATH "UPDATE server_desc SET online_pid = %u WHERE active = 1 AND online_pid = 0 AND daemon_dir = \"%s\""

#define DB_UNLOCK_SQL__PID "UPDATE server_desc SET online_pid = 0 WHERE active = 1 AND online_pid = %u"

#define DB_TEST_UNIQ_SQL__PID "SELECT count(*) FROM server_desc WHERE online_pid = %u"

#define DB_SELECT_SERVER_SQL__PID "SELECT server_id, listen_ip, port, ext_port, daemon_user, daemon_dir, error_log_path, srv_log_path, dbg_lvl,num_net_threads,\
num_worker_threads, version_control_system_name, http_port FROM server_desc WHERE online_pid = %u"

#define DB_SELECT_SOCIAL_NET_SQL "SELECT social_net_id, app_id, app_secret, login_path, iframe FROM social_desc"

#define DB_GET_OTHER_SERVERS_SQL__PID "SELECT server_id, listen_ip, ext_port FROM server_desc WHERE online_pid != %u AND online_pid != 0"

#define DB_GET_ONLINE_USER__UID "SELECT online_server_id FROM logins WHERE uid = %u"

#define DB_GET_USER_LOGIN__UID "SELECT uid, social_id, social_net_id, db_id, online_server_id FROM logins WHERE uid = %u"

#define DB_SET_USER_SERVER_OWNER__SERVER_ID_UID "UPDATE logins SET online_server_id = %u WHERE uid = %u"

#define DB_GET_TABLE_FORMAT SHOW COLUMNS FROM user_data;

#define DB_GET_USER_DATA__UID "SELECT uid, social_id, social_net_id, first_name, last_name, nick_name, sex, money, gold, exp, lvl, music, sound, is_admin,\
last_join_utime, registration_utime,language, invited_friends, friends_data, app_friends_data, avatar, max_energy_endtime, bullets FROM user_data WHERE uid =\
%u"

#define DB_RESET_ALL_USERS_IN_MEMORY__SERVER_ID "UPDATE logins SET online_server_id = 0 WHERE online_server_id = %u"
///--------------
///---DICTIONARIES---
#define DB_GET_DICT_BOSS "SELECT ml_name, ml_description, ml_image, hp, need_obj, give_obj FROM dict_boss"
#define DB_GET_DICT_LANG "SELECT name_uniq, ru, eng FROM dict_lang"
#define DB_GET_DICT_LOCATION "SELECT ml_name, ml_description, ml_image, time, need_obj, lose_reward_obj, win_reward_obj FROM dict_location"
#define DB_GET_DICT_OBJECT "SELECT id, ml_name, ml_desc, ml_image, type FROM dict_object"
#define DB_GET_DICT_PACK "SELECT pack, in_pack_obj, count, dict_pack.group FROM dict_pack"
#define DB_GET_DICT_SHOP "SELECT object, exchange_obj, count, dict_shop.group FROM dict_shop"
///---END---
#define DB_GET_UID_FROM__SOC_ID_SOC_NET_NAME "SELECT uid FROM logins WHERE social_id = %llu and social_net_id = %u"
///---NEW USER---
#define DB_USER_DATA_GET_NEW_USER_FOR_UPDATE "SELECT uid FROM user_data WHERE social_id = 0 LIMIT 1 FOR UPDATE"

#define DB_USER_DATA_PRE_CREATE_NEW_USERS "CALL preCreateUsers()"

#define DB_GET_NEW_USER_FOR_UPDATE "SELECT uid FROM logins WHERE db_id = 0 AND online_server_id = 0 LIMIT 1 FOR UPDATE"

#define DB_UPDATE_LOCKED_FOR_UPDATE "UPDATE logins SET social_id = %llu, social_net_id = %u, db_id = %u, online_server_id = %u WHERE uid = %u"

#define DB_USER_DATA_UPDATE_LOCKED_FOR_UPDATE__NEWUID_OLDUID "UPDATE user_data SET uid = %u WHERE uid = %u"

#define DB_PRE_CREATE_NEW_USERS "CALL preCreateUsers()"
///---END---

#define DB_CREATE_MAIN_DB_PROCEDURE "\
    CREATE PROCEDURE preCreateUsers()\
	  NOT DETERMINISTIC\
	  SQL SECURITY DEFINER\
	  COMMENT ''\
      BEGIN\
	DECLARE counter INTEGER;\
	SET counter = 0;\
	WHILE counter < 50 DO\
	  BEGIN\
	  START TRANSACTION;\
	  INSERT IGNORE INTO logins(social_net_id) VALUES('VK');\
	  SET counter = counter + 1;\
	  COMMIT;\
	  END;\
	END WHILE;\
      END"

#endif
