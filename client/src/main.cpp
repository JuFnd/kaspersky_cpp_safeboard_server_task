#include <iostream>
#include <numeric>

#include "Connection.h"

int main(int argc, const char* argv[]) {
    if(argc < 3) {
        throw std::runtime_error("Not enought arguments");
    }
    int port = std::stoi(argv[2]);
    Connection c{SocketAddress{argv[1], static_cast<int16_t>(port)}};
    std::cout << c.read(10) << std::endl;
    return 0;
}