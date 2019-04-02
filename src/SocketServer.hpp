#ifndef __SOCKETSERVER__
#define __SOCKETSERVER__

// CPP libs
#include <functional>

// Local
#include "Types.hpp"
#include "Socket.hpp"

class SocketServer
{
public:
  typedef std::function<void(Socket)> ConnectionListener;
  SocketServer(int);
  ~SocketServer();
  bool start();
  void onConnect(Socket);
  void setOnConnectListener(SocketServer::ConnectionListener const &);

private:
  Socket mainSocket;
  SocketServer::ConnectionListener onConnectListener;
};

#endif