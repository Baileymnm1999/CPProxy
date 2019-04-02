#include <iostream>

#include "SocketServer.hpp"
#include "Socket.hpp"
#include "Proxy.hpp"
#include "Types.hpp"

int main(void)
{
    SocketServer s = SocketServer(80);
    s.setOnConnectListener(
        [](Socket socket) {
            printf("New Connection...\n");
            Proxy(socket).startInstance();
        });
    s.start();
}