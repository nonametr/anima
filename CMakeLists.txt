PROJECT(anima)

# ADD_EXECUTABLE(anima_login ./login_server/main_login.cpp ./login_server/login_server.h 
# ./login_server/login_server.cpp ./login_server/login_server_handler.h ./login_server/login_server_handler.cpp 
# ./shared/common.h ./shared/common.cpp ./shared/singleton.h ./shared/config.h ./shared/config.cpp ./shared/socket.h 
# ./shared/socket.cpp ./shared/socket_operations.h ./shared/socket_base.h ./shared/net_core.h ./shared/net_core.cpp 
# ./shared/thread.h ./shared/thread.cpp ./shared/thread_core.h ./shared/thread_core.cpp 
# ./shared/periodic_thread_caller.h ./shared/periodic_thread_caller.cpp ./shared/json.h 
# ./shared/json.cpp ./shared/json_value.h ./shared/json_value.cpp ./shared/version_control.h ./shared/version_control.cpp)

# target_link_libraries (anima_login z mysqlclient pthread)



ADD_EXECUTABLE(anima_game 
./game_server/main_game.cpp 
./login_server/login_server.h 
./login_server/login_server.cpp 
./login_server/login_server_handler.h 
./login_server/login_server_handler.cpp
./game_server/game_server.h 
./game_server/game_server.cpp 
./game_server/game_socket.h
./game_server/game_socket.cpp 
./game_server/server.h 
./game_server/server.cpp 
./game_server/database_manager.h 
./game_server/database_manager.cpp 
./shared/common.h 
./shared/common.cpp 
./shared/singleton.h 
./shared/config.h 
./shared/config.cpp 
./shared/net/socket.h 
./shared/net/socket.cpp 
./shared/net/socket_operations.h 
./shared/net/socket_base.h 
./shared/net/net_core.h 
./shared/net/net_core.cpp 
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
./game_server/storage/ext_interface.h 
./game_server/storage/ext_interface.cpp 
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
./dict_json_generator.h 
./dict_json_generator.cpp
)

target_link_libraries (anima_game z mysqlclient pthread)
add_definitions(-Wall -Werror -std=c++0x) 

add_subdirectory(login_server)
add_subdirectory(game_server)
