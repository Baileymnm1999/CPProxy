#ifndef __PROXY__
#define __PROXY__

#include "Socket.hpp"

class Proxy
{
  private:
    Socket client;

  public:
    Proxy(Socket);
    ~Proxy();
    void startInstance();
};

#endif