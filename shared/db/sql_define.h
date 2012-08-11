#ifndef SQL_DEFINE_H
#define SQL_DEFINE_H

#define DB_GET_DESC "SELECT db_id, name, ip, port, user, password, charset FROM db_desc WHERE active = 1"

#define DB_GET_COUNT "SELECT MAX(db_id)+1 FROM db_desc WHERE active = 1"

#define DB_LOCK_SQL__PID_WORK_PATH "UPDATE server_desc SET online_pid = %u WHERE active = 1 AND online_pid = 0 AND daemon_dir = \"%s\""

#define DB_UNLOCK_SQL__PID "UPDATE server_desc SET online_pid = 0 WHERE active = 1 AND online_pid = %u"

#define DB_TEST_UNIQ_SQL__PID "SELECT count(*) FROM server_desc WHERE online_pid = %u"

#define DB_SELECT_SERVER_SQL__PID "SELECT server_id, listen_ip, port, ext_port, daemon_user, daemon_dir, error_log_path, srv_log_path, dbg_lvl,num_net_threads,\
num_worker_threads, version_control_system_name, http_port FROM server_desc WHERE online_pid = %u"

#define DB_SELECT_SOCIAL_NET_SQL "SELECT social_net_id, app_id, app_secret, login_path, iframe, iframe_friend_rq FROM social_desc"

#define DB_GET_OTHER_SERVERS_SQL__PID "SELECT server_id, listen_ip, ext_port FROM server_desc WHERE online_pid != %u AND online_pid != 0"

#define DB_GET_ONLINE_USER__UID "SELECT online_server_id FROM logins WHERE uid = %u"

#define DB_GET_USER_LOGIN__UID "SELECT uid, social_id, social_net_id, db_id, online_server_id FROM logins WHERE uid = %u"

#define DB_SET_USER_SERVER_OWNER__SERVER_ID_UID "UPDATE logins SET online_server_id = %u WHERE uid = %u"

#define DB_GET_USER_DATA__UID "SELECT * FROM user_data WHERE uid = %u"

#define DB_GET_USER_DATA_PRIVATE__UID "SELECT * FROM user_data_private WHERE uid = %u"

#define DB_GET_USER_DATA_OBJECTS__UID "SELECT * FROM user_data_objects WHERE uid = %u"

#define DB_RESET_ALL_USERS_IN_MEMORY__SERVER_ID "UPDATE logins SET online_server_id = 0 WHERE online_server_id = %u"
///--------------
///---DICTIONARIES---
#define DB_GET_DICT_BOSS "SELECT * FROM dict_boss"
#define DB_GET_DICT_BOSS_STRIKE "SELECT * FROM dict_boss_strike"
#define DB_GET_DICT_MESSAGES "SELECT * FROM dict_message"
#define DB_GET_DICT_SWF_OBJECT "SELECT * FROM dict_swf_object"
#define DB_GET_DICT_ML_INTERFACE "SELECT * FROM dict_multilang_interface"
#define DB_GET_DICT_LANG "SELECT * FROM dict_lang"
#define DB_GET_DICT_LOCATION "SELECT * FROM dict_location"
#define DB_GET_DICT_MSG "SELECT * FROM dict_message"
#define DB_GET_DICT_OBJECT "SELECT * FROM dict_object"
#define DB_GET_DICT_OBJECT_TYPES "SELECT dict_object_types.type, dict_object_types.table FROM dict_object_types"
#define DB_GET_OBJECT_INFO__TABLE_OBJECT_NAME "SELECT * FROM %s WHERE object = \"%s\""
#define DB_GET_DICT_PACK "SELECT * FROM dict_pack"
#define DB_GET_DICT_GIVE "SELECT * FROM dict_give"
#define DB_GET_DICT_EXCHANGE "SELECT * FROM dict_exchange"
#define DB_GET_DICT_DROP_CHANCE "SELECT * FROM dict_drop_chance"
#define DB_GET_DICT_DROP_CHANCE__OBJ_IN_PACK "SELECT chance_max_10000 FROM dict_drop_chance WHERE object = \"%s\" AND in_pack_obj = \"%s\""
///---END---
#define DB_GET_UID_FROM__SOC_ID_SOC_NET_NAME "SELECT uid FROM logins WHERE social_id = %llu and social_net_id = %u"
#define DB_GET_UID_LVL_EXP_FROM_USER_RATING_DATA__SOC_ID "SELECT uid, social_id, lvl, exp FROM user_rating_data WHERE social_id in (%s)"
///---NEW USER---
#define DB_USER_DATA_GET_NEW_USER_FOR_UPDATE "SELECT uid FROM user_data WHERE active = 0 LIMIT 1 FOR UPDATE"
#define DB_USER_OBJECT_GET_NEW_USER_FOR_UPDATE "SELECT uid FROM user_data_objects WHERE active = 0 LIMIT 1 FOR UPDATE"
#define DB_USER_PRIVATE_GET_NEW_USER_FOR_UPDATE "SELECT uid FROM user_data_private WHERE active = 0 LIMIT 1 FOR UPDATE"

#define DB_USER_DATA_PRE_CREATE_NEW_USERS "CALL preCreateUsers()"

#define DB_GET_NEW_USER_FOR_UPDATE "SELECT uid FROM logins WHERE db_id = 0 LIMIT 1 FOR UPDATE"

#define DB_UPDATE_LOCKED_FOR_UPDATE "UPDATE logins SET social_id = %lu, social_net_id = %u, db_id = %u WHERE uid = %u"

#define DB_USER_DATA_UPDATE_LOCKED_FOR_UPDATE__NEWUID_OLDUID "UPDATE user_data SET uid = %u, active = 1 WHERE uid = %u"
#define DB_USER_OBJECT_UPDATE_LOCKED_FOR_UPDATE__NEWUID_OLDUID "UPDATE user_data_objects SET uid = %u, active = 1 WHERE uid = %u"
#define DB_USER_PRIVATE_UPDATE_LOCKED_FOR_UPDATE__NEWUID_OLDUID "UPDATE user_data_private SET uid = %u, active = 1 WHERE uid = %u"

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
