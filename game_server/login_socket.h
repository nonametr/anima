#ifndef LOGINSERVERHANDLER_H
#define LOGINSERVERHANDLER_H

#include "socket.h"
#include "listen_socket.h"

class LoginSocket;

struct SocialNetDesc 
{
  enum {VK = 0, MM, OK, FB, MAX_SOC};
  string app_id;
  string app_secret;
  string login_path;
  string (LoginSocket::*handler)(string &data);
  string iframe;
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
    string getJsonParamStr(string &data, string param);
    string getJsonParamInt(string &data, string param);
    string getParam(string &data, string param);
    string vkReq(string &data);
    string okReq(string &data);
    string mmReq(string &data);
    string fbReq(string &data);
    string statReq(string &data);
    
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
