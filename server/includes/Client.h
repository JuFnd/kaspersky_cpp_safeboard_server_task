#pragma once

#include "Socket.h"
#include "SocketAddress.h"

class Client {
private:
    int file_descriptor;
public:
    
    int getFd();
    void accept(int server_file_descriptor);
    void close();
    
    Client& operator=(Client&& other);
    Client& operator=(const Client& other) = delete;
    
    Client(const Client& other) = delete;
    Client(Client&& other) noexcept;
    Client();
    ~Client();
};