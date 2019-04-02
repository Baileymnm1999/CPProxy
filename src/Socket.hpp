#ifndef __SOCKET__
#define __SOCKET__

#include <netinet/in.h>

// Local
#include "Types.hpp"

class Socket
{
  private:
    int socketFd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

  public:
    Socket(int = 0);
    ~Socket();
    bool initialize(int = AF_INET, int = SOCK_STREAM, int = 0);
    bool bind(int);
    bool listen(int = 10);
    Socket await();
    bool kill();
    bool send(String);
    String recvs();
};

#endif