#include "Client.h"

Client::Client(): file_descriptor(-1) {
    
}

Client::Client(Client&& other) noexcept {
    file_descriptor = std::exchange(other.file_descriptor, -1);
}

Client& Client::operator=(Client&& other) {
    try {
        close();
    } catch(...) {
    }
    file_descriptor = std::exchange(other.file_descriptor, -1);
    return *this;
}

Client::~Client() {
    try
    {
        close();
    }
    catch(...){
    }
    
}

void Client::accept(int server_file_descriptor) {
    SocketAddress address;
    socklen_t addres_length = sizeof(address.getAddr());
    ::sockaddr* sock_addr_ptr = reinterpret_cast<::sockaddr*>(&address);


    file_descriptor = ::accept(server_file_descriptor, sock_addr_ptr, &addres_length);
}

void Client::close() {
    if(file_descriptor != -1) {
        int result = ::close(file_descriptor);
        file_descriptor = -1;
        if(result < 0) {
           using namespace std::string_literals;
           throw std::runtime_error("Cannot correct close socket "s + std::strerror(errno));
        }
    }
}

int Client::getFd() {
    return file_descriptor;
}