#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>

// Local
#include "Socket.hpp"

Socket::Socket(int socketDesc)
{
    if (socketDesc)
        socketFd = socketDesc;
}

Socket::~Socket()
{
}

bool Socket::initialize(int domain, int type, int protocol)
{
    // Creating socket file descriptor
    if ((socketFd = socket(domain, type, protocol)) == 0)
    {
        return false;
    }

    // Force reuse
    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        return false;
    }
    address.sin_family = domain;
    address.sin_addr.s_addr = INADDR_ANY;
    return true;
}

bool Socket::bind(int port)
{
    // Forcefully attaching socket to the port
    address.sin_port = htons(port);
    if (::bind(socketFd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        return false;
    }
    return true;
}

bool Socket::listen(int queue)
{
    if (::listen(socketFd, queue) < 0)
    {
        return false;
    }
    return true;
}

Socket Socket::await()
{
    int newSocket;
    if ((newSocket = accept(socketFd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("Accept");
        exit(-1);
    }
    return Socket(newSocket);
}

bool Socket::kill()
{
    return (close(socketFd) == 0);
}

bool Socket::send(String data)
{
    ::send(socketFd, data.c_str(), data.size(), 0);
}

String Socket::recvs()
{
    char buf[4096] = {0};
    // memset(buf, 0, 4096);
    ::recv(socketFd, buf, sizeof(buf), 0);
    return String(buf);
}