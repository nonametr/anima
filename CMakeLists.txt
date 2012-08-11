cmake_minimum_required(VERSION 2.8)
PROJECT(anima)

add_executable(
anima_game 
./shared/net/netcore_worker_thread.cpp 
./game_server/main_game.cpp
./shared/exeption.cpp 
./shared/common.cpp
./shared/random.cpp
./shared/urlencode.cpp
./shared/config.cpp
./shared/net/socket.cpp
./shared/net/net_core.cpp
./shared/net/command_structs.cpp
./shared/mt/thread.cpp 
./shared/mt/thread_core.cpp 
./shared/mt/periodic_thread_caller.cpp 
./shared/json.cpp 
./shared/json_value.cpp 
./shared/version_control.cpp
./shared/db/database.cpp
./shared/db/mysql_database.cpp
./game_server/login/login_socket.cpp
./game_server/login/login_service.cpp
./game_server/login/login_vk.cpp
./game_server/game_server.cpp 
./game_server/game_socket.cpp 
./game_server/server.cpp 
./game_server/debug_update.cpp
./game_server/database_manager.cpp
./game_server/storage/storage_thread.cpp
./game_server/storage/storage_timer.cpp
./game_server/storage/ext_socket.cpp 
./game_server/storage/ext_server_manager.cpp 
./game_server/storage/storage.cpp 
./game_server/instance/instance.cpp
./game_server/instance/main_instance.cpp 
./game_server/instance/ext_socket_instance.cpp
./game_server/ratings/rating_manager.cpp
./game_server/user/boss.cpp 
./game_server/user/value.cpp 
./game_server/user/object_list.cpp 
./game_server/user/location.cpp 
./game_server/user/user.cpp 
./game_server/user/user_ext.cpp 
./game_server/user/object.cpp 
./game_server/dict/dict_manager.cpp 
./game_server/dict/dict_object.cpp 
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
./game_server/dict
./game_server/ratings
./game_server/login
./
)

target_link_libraries (anima_game z mysqlclient pthread crypto)
add_definitions(-Wall -Werror -std=c++0x) 

add_subdirectory(game_server)

add_subdirectory(shared/json)