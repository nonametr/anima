PROJECT(anima)

# ADD_EXECUTABLE(anima_login ./login_server/main_login.cpp ./login_server/login_server.h 
# ./login_server/login_server.cpp ./login_server/login_server_handler.h ./login_server/login_server_handler.cpp 
# ./shared/common.h ./shared/common.cpp ./shared/singleton.h ./shared/config.h ./shared/config.cpp ./shared/socket.h 
# ./shared/socket.cpp ./shared/socket_operations.h ./shared/socket_base.h ./shared/net_core.h ./shared/net_core.cpp 
# ./shared/thread.h ./shared/thread.cpp ./shared/thread_core.h ./shared/thread_core.cpp 
# ./shared/periodic_thread_caller.h ./shared/periodic_thread_caller.cpp ./shared/json.h 
# ./shared/json.cpp ./shared/json_value.h ./shared/json_value.cpp ./shared/version_control.h ./shared/version_control.cpp)

# target_link_libraries (anima_login z mysqlclient pthread)



ADD_EXECUTABLE(anima_game ./game_server/main_game.cpp ./game_server/game_server.h 
./game_server/game_server.cpp ./game_server/shard.h ./game_server/shard.cpp ./shared/common.h 
./shared/common.cpp ./shared/singleton.h ./shared/config.h ./shared/config.cpp ./shared/socket.h 
./shared/socket.cpp ./shared/socket_operations.h ./shared/socket_base.h ./shared/net_core.h ./shared/net_core.cpp 
./shared/thread.h ./shared/thread.cpp ./shared/thread_core.h ./shared/thread_core.cpp 
./shared/periodic_thread_caller.h ./shared/periodic_thread_caller.cpp ./shared/json.h 
./shared/json.cpp ./shared/json_value.h ./shared/json_value.cpp ./shared/version_control.h ./shared/version_control.cpp
./shared/database.h ./shared/database.cpp ./shared/mysql_database.h ./shared/mysql_database.cpp ./game_server/shard_ext.h 
./game_server/shard_ext.cpp ./game_server/shard_storage.h ./game_server/shard_storage.cpp ./game_server/user.h 
./game_server/user.cpp ./game_server/user_ext.h ./game_server/user_ext.cpp ./shared/smart_pointer.h)

target_link_libraries (anima_game z mysqlclient pthread)
add_definitions(-Wall -Werror -std=c++0x) 

add_subdirectory(login_server)
add_subdirectory(game_server)
add_subdirectory(super_server)