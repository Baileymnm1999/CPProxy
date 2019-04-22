#ifndef __SOCKETSERVER__
#define __SOCKETSERVER__

// CPP libs
#include <functional>
#include <thread>

// Local
#include "Types.hpp"
#include "Socket.hpp"

class SocketServer
{
public:
  typedef std::function<void(Socket)> ConnectionListener;
  SocketServer(int = 8080);
  ~SocketServer();
  Thread start();
  void onConnect(Socket);
  void setOnConnectListener(ConnectionListener const &);

private:
  Socket mainSocket;
  ConnectionListener onConnectListener;
};

#endif