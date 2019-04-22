#include <iostream>
#include <thread>

#include "SocketServer.hpp"
#include "Socket.hpp"
#include "Proxy.hpp"
#include "Types.hpp"

int main(void)
{
    auto listener = [](Socket socket) {
        printf("New Connection on 88...\n");
        Proxy(socket).startInstance(Proxy::HTTP);
    };

    SocketServer s1 = SocketServer(88);
    s1.setOnConnectListener(listener);
    auto t1 = s1.start();

    t1.join();

    return 0;
}