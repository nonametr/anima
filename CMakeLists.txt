PROJECT(anima)

cmake_minimum_required(VERSION 2.8)

add_executable(
anima_game game_server/user/object.cpp 
./shared/net/netcore_worker_thread.h
./shared/net/netcore_worker_thread.cpp 
./game_server/main_game.cpp
./shared/common.h 
./shared/common.cpp 
./shared/urlencode.h 
./shared/urlencode.cpp 
./shared/singleton.h 
./shared/config.h 
./shared/config.cpp 
./shared/net/socket.h 
./shared/net/socket.cpp 
./shared/net/socket_operations.h 
./shared/net/socket_base.h 
./shared/net/net_core.h 
./shared/net/net_core.cpp 
./shared/net/command_structs.h 
./shared/net/command_structs.cpp 
./shared/mt/thread.h 
./shared/mt/thread.cpp 
./shared/mt/thread_core.h 
./shared/mt/thread_core.cpp 
./shared/mt/periodic_thread_caller.h 
./shared/mt/periodic_thread_caller.cpp 
./shared/json.h 
./shared/json.cpp 
./shared/json_value.h 
./shared/json_value.cpp 
./shared/version_control.h 
./shared/version_control.cpp
./shared/db/database.h
./shared/db/database.cpp
./shared/db/mysql_database.h
./shared/db/mysql_database.cpp
./shared/smart_pointer.h
./game_server/login_socket.h 
./game_server/login_socket.cpp
./game_server/game_server.h 
./game_server/game_server.cpp 
./game_server/game_socket.h
./game_server/game_socket.cpp 
./game_server/server.h 
./game_server/server.cpp 
./game_server/debug_update.h 
./game_server/debug_update.cpp
./game_server/database_manager.h 
./game_server/database_manager.cpp
./game_server/storage/storage_thread.h 
./game_server/storage/storage_thread.cpp
./game_server/storage/storage_timer.h
./game_server/storage/storage_timer.cpp
./game_server/storage/ext_socket.h 
./game_server/storage/ext_socket.cpp 
./game_server/storage/ext_server_manager.h
./game_server/storage/ext_server_manager.cpp 
./game_server/storage/storage.h 
./game_server/storage/storage.cpp 
./game_server/user/user.h 
./game_server/user/user.cpp 
./game_server/user/user_ext.h 
./game_server/user/user_ext.cpp 
./game_server/instance/instance.h 
./game_server/instance/instance.cpp
./game_server/instance/main_instance.h 
./game_server/instance/main_instance.cpp 
./game_server/instance/ext_socket_instance.h
./game_server/instance/ext_socket_instance.cpp
./dict_json_generator.h 
./dict_json_generator.cpp
)

include_directories(
./shared 
./shared/db 
./shared/mt 
./shared/net 
./game_server 
./game_server/instance 
./game_server/storage 
./game_server/user  
./
)

target_link_libraries (anima_game z mysqlclient pthread crypto)
add_definitions(-Wall -Werror -std=c++0x) 

add_subdirectory(game_server)
