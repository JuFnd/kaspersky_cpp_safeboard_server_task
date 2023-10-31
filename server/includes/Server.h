#pragma once

#include <thread>
#include <string>
#include <mutex>

#include "Client.h"

#include <iostream>
#include <cstring>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

class Server {
private:
    Socket socket;
    std::mutex mutex;

public:
    void send(Client&& client);
    void listen();
    void bind(const SocketAddress& address);
    int getFd();

    Server(const SocketAddress& address);
};
