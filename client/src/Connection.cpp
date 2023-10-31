#include "Connection.h"

Connection::Connection(const SocketAddress& address) {
    connect(address);
}

void Connection::connect(const SocketAddress& address) {
    Socket tmp;
    const ::sockaddr_in& sock_addr = address.getAddr();
    const ::sockaddr* sock_addr_ptr = reinterpret_cast<const ::sockaddr*>(&sock_addr);

    int connection_result = ::connect(tmp.getFd(), sock_addr_ptr, sizeof(sock_addr));
    if(connection_result < 0) {
           using namespace std::string_literals;
           throw std::runtime_error("Cannot connect to "s + std::strerror(errno));
    }
    socket = std::move(tmp);
}

std::string Connection::read(size_t byte) {
    if (!socket.isOpen()) {
        using namespace std::string_literals;
        throw std::runtime_error("Socket is not connected");
    }

    uint32_t size;
    ssize_t bytesRead = ::read(socket.getFd(), &size, sizeof(size));
    if (bytesRead < 0) {
        using namespace std::string_literals;
        throw std::runtime_error("Error reading message size: "s + std::strerror(errno));
    }
    if (bytesRead == 0) {
        throw std::runtime_error("Connection closed by peer");
    }
    if (bytesRead != sizeof(size)) {
        throw std::runtime_error("Incomplete message size read");
    }

    size_t messageSize = ntohl(size);

    std::string buffer;
    buffer.resize(messageSize);
    size_t toRead = messageSize;
    while (toRead > 0) {
        ssize_t bytesRead = ::read(socket.getFd(), buffer.data() + messageSize - toRead, toRead);
        if (bytesRead == 0) {
            throw std::runtime_error("Connection closed by peer");
        }
        if (bytesRead < 0) {
            using namespace std::string_literals;
            throw std::runtime_error("Error reading message: "s + std::strerror(errno));
        }
        toRead -= bytesRead;
    }

    return buffer;
}


void Connection::write(const std::string& str) {
    if(!socket.isOpen()) {
           using namespace std::string_literals;
           throw std::runtime_error("Socket is not connected");
    }

    std::string_view to_write = str;   
    while(!to_write.empty()) {
        ssize_t written = ::write(socket.getFd(), to_write.data(), to_write.size());

        if(written < 0) {
           using namespace std::string_literals;
           throw std::runtime_error("Error writting message "s + std::strerror(errno));
        }

        to_write.remove_prefix(written);
    }
}

void Connection::close() {
    socket.close();
}