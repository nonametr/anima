project(anima)

add_executable(anima_login ./login_server/main_login.cpp ./shared/common.h ./shared/common.cpp ./shared/singleton.h ./shared/config.h ./shared/config.cpp ./shared/socket.h ./shared/socket.cpp ./shared/socket_operations.h ./shared/socket_base.h ./shared/netcore.h ./shared/netcore.cpp ./shared/thread.h ./shared/thread.cpp ./shared/threadcore.h ./shared/threadcore.cpp ./shared/periodicthreadcaller.h ./shared/periodicthreadcaller.cpp ./shared/json.h ./shared/json.cpp ./shared/jsonvalue.h ./shared/jsonvalue.cpp ./login_server/loginserver.h ./login_server/loginserver.cpp ./login_server/loginserverhandler.h ./login_server/loginserverhandler.cpp ./shared/version_control.h ./shared/version_control.cpp)
add_subdirectory(login_server)
add_subdirectory(game_server)