#include "Socket.h"

Socket::Socket() {
    file_descriptor = ::socket(AF_INET, SOCK_STREAM, 0);
    if(file_descriptor == -1) {
        using namespace std::string_literals;
        throw std::runtime_error("Cannot create socket "s + std::strerror(errno));
    }
}

Socket::Socket(Socket&& other) noexcept {
    file_descriptor = std::exchange(other.file_descriptor, -1);
}

Socket::~Socket() {
    try{
       close();
    } catch(...) {
    }
}

Socket& Socket::operator=(Socket&& other) {
    try {
        close();
    } catch(...) {
    }
    file_descriptor = std::exchange(other.file_descriptor, -1);
    return *this;
}

bool Socket::isOpen() const {
    return file_descriptor != -1;
}

int Socket::getFd() {
    return file_descriptor;
}

void Socket::close() {
    if(file_descriptor != -1) {
        int result = ::close(file_descriptor);
        file_descriptor = -1;
        if(result < 0) {
           using namespace std::string_literals;
           throw std::runtime_error("Cannot correct close socket "s + std::strerror(errno));
        }
    }
}