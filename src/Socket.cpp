#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
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

bool Socket::connect(String host, int port)
{
    memset(&hostAddress, '0', sizeof(hostAddress));

    hostAddress.sin_family = AF_INET;
    hostAddress.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, host.c_str(), &hostAddress.sin_addr) <= 0)
    {
        hostent *record = gethostbyname(host.c_str());
        if (record == NULL)
        {
            printf("%s is unavailable\n", host.c_str());
            return 0;
        }
        in_addr *address = (in_addr *)record->h_addr;
        char *ip_address = inet_ntoa(*address);

        if (inet_pton(AF_INET, ip_address, &hostAddress.sin_addr) <= 0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return 0;
        }
    }

    if (::connect(socketFd, (struct sockaddr *)&hostAddress, sizeof(hostAddress)) < 0)
    {
        printf("\nConnection Failed \n");
        return 0;
    }
    return 1;
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
    size_t s = 1024 * 1024;
    char *buf = (char *)malloc(s);
    if (::recv(socketFd, buf, s, 0) < 0)
    {
        std::cout << "Disconect";
        return "";
    }
    String ret = String(buf);
    // free(buf);
    return ret;
}