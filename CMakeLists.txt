PROJECT(anima)

ADD_EXECUTABLE(anima_login ./login_server/main_login.cpp ./shared/common.h ./shared/common.cpp 
./shared/singleton.h ./shared/config.h ./shared/config.cpp ./shared/socket.h ./shared/socket.cpp 
./shared/socket_operations.h ./shared/socket_base.h ./shared/net_core.h ./shared/net_core.cpp 
./shared/thread.h ./shared/thread.cpp ./shared/thread_core.h ./shared/thread_core.cpp 
./shared/periodic_thread_caller.h ./shared/periodic_thread_caller.cpp ./shared/json.h 
./shared/json.cpp ./shared/json_value.h ./shared/json_value.cpp ./login_server/login_server.h 
./login_server/login_server.cpp ./login_server/login_server_handler.h ./login_server/login_server_handler.cpp 
./shared/version_control.h ./shared/version_control.cpp)

ADD_SUBDIRECTORY(login_server)
ADD_SUBDIRECTORY(game_server)

