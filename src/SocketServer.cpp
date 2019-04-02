#include <unistd.h>
#include <thread>
#include <future>
#include "SocketServer.hpp"
#include "Socket.hpp"

SocketServer::SocketServer(int port)
{
    mainSocket = Socket();
    if (!mainSocket.initialize())
    {
        perror("Initialization");
        exit(-1);
    };
    if (!mainSocket.bind(port))
    {
        perror("Binding");
        exit(-1);
    };
}

SocketServer::~SocketServer()
{
}

bool SocketServer::start()
{
    if (!mainSocket.listen())
    {
        return false;
    }
    while (1)
    {
        Socket newSocket = mainSocket.await();
        onConnect(newSocket);
    }
}

void SocketServer::onConnect(Socket conn)
{
    // launch in new process
    int pid = fork();
    if (pid < 0)
    {
        throw 1;
    }
    else if (pid == 0)
    {
        mainSocket.kill();
        onConnectListener(conn);
        exit(0);
    }
}

void SocketServer::setOnConnectListener(SocketServer::ConnectionListener const &listener)
{
    onConnectListener = listener;
}