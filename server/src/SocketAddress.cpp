#include "SocketAddress.h"

SocketAddress::SocketAddress(const std::string& ip, short port) : addr{} {
    addr.sin_family = AF_INET;
    addr.sin_port = ::htons(port);

    int parse_status = ::inet_aton(ip.c_str(), &addr.sin_addr);
    if(parse_status == 0) {
           using namespace std::string_literals;
           throw std::runtime_error("Cannot parse ip from string "s + std::strerror(errno));
    }

}

SocketAddress::SocketAddress() { 
    addr = ::sockaddr_in{};
}

const ::sockaddr_in& SocketAddress::getAddr() const {
    return addr;
}