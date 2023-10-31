#pragma once

#include "Socket.h"
#include "SocketAddress.h"

#include <string_view>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h> 

class Connection {
private:
    Socket socket;

public:
    Connection() = default;
    explicit Connection(const SocketAddress& address);

    void write(const std::string& str);
    std::string read(size_t byte);

    void connect(const SocketAddress& address);
    void close();
};