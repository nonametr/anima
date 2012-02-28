#ifndef SQL_DEFINE_H
#define SQL_DEFINE_H

#define DB_GET_DESC "SELECT db_id, name, ip, port, user, password, charset FROM db_desc WHERE active = 1"
#define DB_GET_COUNT "SELECT MAX(db_id)+1 FROM db_desc WHERE active = 1"
#define DB_LOCK_SQL__PID_WORK_PATH "UPDATE server_desc SET online_pid = %u WHERE active = 1 AND online_pid = 0 AND daemon_dir = \"%s\""
#define DB_UNLOCK_SQL__PID "UPDATE server_desc SET online_pid = 0 WHERE active = 1 AND online_pid = %u"
#define DB_TEST_UNIQ_SQL__PID "SELECT count(*) FROM server_desc WHERE online = %u"
#define DB_SELECT_SERVER_SQL__PID "SELECT server_id, listen_ip, port, ext_port, daemon_user, daemon_dir, error_log_path, srv_log_path, dbg_lvl, num_net_threads, num_worker_threads, version_control_system_name, server_type FROM server_desc WHERE online_pid = %u"
#define DB_GET_OTHER_SERVERS_SQL__PID "SELECT server_id, listen_ip, ext_port, server_type FROM server_desc WHERE online != %u AND online != 0"
#define DB_GET_ONLINE_USER__UID "SELECT online FROM login WHERE uid = %u"
#define DB_GET_USER_LOGIN__UID "SELECT uid, social_id, social_net_name, db_id, online FROM logins WHERE uid = %u"
#define DB_SET_USER_SERVER_OWNER__SERVER_ID "UPDATE login SET online = %u"

#define DB_GET_USER_DATA__UID "SELECT uid, social_id, social_net_name, first_name, last_name, nick_name, sex, money, \
gold, exp, lvl, music, sound, is_admin, last_join_utime, registration_utime,language, invited_friends, friends_data, app_friends_data FROM user_data WHERE uid = %u"

///---NEW USER---
#define DB_GET_NEW_USER_FOR_UPDATE "SELECT uid FROM logins WHERE db_id = 0 AND online = 0 LIMIT 1 FOR UPDATE"
#define DB_UPDATE_LOCKED_FOR_UPDATE "UPDATE logins SET social_id = %ull, social_net_name = %u, db_id = %u, online = %u WHERE uid = %u"
#define DB_CREATE_USER_GAME_DB__UID "INSERT INTO ho_gs(uid) VALUES(%u)"
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
	  INSERT IGNORE INTO logins(social_net_name) VALUES('VK');\
	  SET counter = counter + 1;\
	  COMMIT;\
	  END;\
	END WHILE;\
      END"

#endif