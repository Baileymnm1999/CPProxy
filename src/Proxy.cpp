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
    try
    {
        handleClient(proto);
    }
    catch (int i)
    {
        std::cout << "Invalid Request\n";
    }
    client.kill();
}

String Proxy::handleClient(int proto)
{
    switch (proto)
    {
    case HTTP:
    {
        handleHttp();
        break;
    }
    default:
    {
        break;
    }
    }
}

void Proxy::handleHttp()
{
    // HttpHandler h = HttpHandler();
    // String newReq = h.parseRequest(client.recvs()).getRequest();
    // std::cout << "Forwarding:\n"
    //   << newReq;
    // Socket s = forward(newReq, h.getHost(), h.getPort());
    // String data;
    // do
    // {
    //     data = s.recvs();
    //     break;
    //     client.send(data);
    // } while (!data.empty());

    // s.kill();
}

Socket Proxy::forward(String data, String host, int port)
{
    Socket s = Socket();
    s.initialize();
    s.connect(host, port);
    s.send(data);

    return s;
}
