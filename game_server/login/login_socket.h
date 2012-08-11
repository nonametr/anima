#ifndef LOGINSERVERHANDLER_H
#define LOGINSERVERHANDLER_H

#include "socket.h"
#include "listen_socket.h"
#include "json.h"
#include "json_value.h"

#define HTML_HEADER "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: "

class User;
class LoginSocket;

struct SocialNetDesc 
{
  enum {VK = 0, MM, OK, FB, MAX_SOC};
  string app_id;
  string app_secret;
  string login_path;
  string (LoginSocket::*handler)(string &data);
  string iframe;
  string iframe_fr_req;
};

class LoginSocketThread : public Thread
{
public:
    void run();
    void onShutdown();
    LoginSocketThread(LoginSocket *p_owner);
    virtual ~LoginSocketThread();
private:
    LoginSocket *_owner;
    volatile bool _running;
};

class LoginSocket : public ListenSocket
{
    friend class LoginSocketThread;
public:
    void updateDb();
    LoginSocket(const char* listen_address, uint32 port);
    virtual ~LoginSocket();
private:
    string vkReq(string &data);
    string okReq(string &data);
    string mmReq(string &data);
    string fbReq(string &data);
    string statReq(string &data);
    string getGameVKIFrame(string &data);
    string cbFriendsVk(string &data);
    string generateVKAppFriends(JSONValue *json, uint db_id);
    string dictRegenerate(string &data);
    
    void onPacketRead(Packet *pkt)
    {
        _data.push(pkt);
    }
    void onPacketDisconnect(Socket *sock) 
    {
        --_conn_count;
    };
    void onPacketConnect(Socket *sock) 
    {
        ++_conn_count;
    };

    void performPacket( Packet *pkt );
    FQueue<Packet*> _data;
    AtomicCounter _conn_count;
    SocialNetDesc _social_net[SocialNetDesc::MAX_SOC];
};

#endif // LOGINSERVERHANDLER_H
