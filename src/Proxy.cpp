#include <iostream>

#include "Proxy.hpp"
#include "Socket.hpp"
#include "Types.hpp"

Proxy::Proxy(Socket s)
{
    client = s;
}

Proxy::~Proxy()
{
}

void Proxy::startInstance()
{
    String req;
    do
    {
        req += client.recvs();
    } while (req.substr(req.size() - 5, 4) != "\r\n\r\n");

    std::cout << "Request:\n"
              << req << std::endl;
    client.kill();
}