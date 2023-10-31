#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <cerrno>
#include <cstring>
#include <string>
#include <stdexcept>
#include <utility>
#include <unistd.h>


class Socket {
private:
    int file_descriptor;

public:
    int getFd();
    void close();

    bool isOpen() const;

    Socket& operator=(Socket&& other);
    Socket& operator=(const Socket& other) = delete;

    Socket();
    Socket(Socket&& other) noexcept;
    Socket(const Socket& other) = delete;
    ~Socket();
};