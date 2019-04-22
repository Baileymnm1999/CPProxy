#include <iostream>
#include <string>

#include "Proxy.hpp"
#include "HttpHandler.hpp"
#include "Socket.hpp"
#include "Types.hpp"

Proxy::Proxy(Socket s)
{
    client = s;
}

Proxy::~Proxy()
{
}

void Proxy::startInstance(int proto)
{
    String req = client.recvs();
    handleRequest(req, proto);

    client.kill();
}

void Proxy::handleRequest(String req, int proto)
{
    String newReq;
    switch (proto)
    {
    case HTTP:
        newReq = HttpHandler().parseRequest(req).getRequest();
        std::cout << newReq << std::endl;
        break;

    default:
        break;
    }
}
