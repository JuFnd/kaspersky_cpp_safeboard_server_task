#include "Server.h"

Server::Server(const SocketAddress& address) {
    bind(address);
}

void Server::bind(const SocketAddress& address) {
    const ::sockaddr_in& sock_addr = address.getAddr();
    const ::sockaddr* sock_addr_ptr = reinterpret_cast<const ::sockaddr*>(&sock_addr);

    int bind_status = ::bind(socket.getFd(), sock_addr_ptr, sizeof(sock_addr));
    if(bind_status < 0) {
        using namespace std::string_literals;
        throw std::runtime_error("Cannot bind "s + std::strerror(errno));
    }
}

void Server::send(Client&& client) {
    std::string message = "kaspersky";
    size_t messageSize = message.size();
    size_t bufferSize = sizeof(messageSize) + messageSize;

    uint32_t networkSize = htonl(messageSize);

    std::lock_guard<std::mutex> lock(mutex);

    ssize_t bytesSent = ::send(client.getFd(), &networkSize, sizeof(networkSize), 0);
    if (bytesSent == -1) {
        std::cerr << "Failed to send message size" << std::endl;
    }

    bytesSent = ::send(client.getFd(), message.c_str(), messageSize, 0);
    if (bytesSent == -1) {
        std::cerr << "Failed to send message" << std::endl;
    }

    client.close();
}

void Server::listen() {
    int listen_status = ::listen(socket.getFd(), 1);
    if(listen_status < 0) {
        using namespace std::string_literals;
        throw std::runtime_error("Listen error "s + std::strerror(errno));
    }
}

int Server::getFd() {
    return socket.getFd();
}
