#pragma once

#include <string>
#include <stdexcept>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

class SocketAddress {
private:
    ::sockaddr_in addr;
public:
    const ::sockaddr_in& getAddr() const; 

    SocketAddress(const std::string& ip, short port);
    SocketAddress();
}; 