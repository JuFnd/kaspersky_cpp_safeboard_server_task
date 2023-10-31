#include "Server.h"
#include "Client.h"

int main() {
    SocketAddress serverAddress("127.0.0.1", 8080);
    Server server(serverAddress);

    server.listen();
    
    while (true) {
        Client client;
        client.accept(server.getFd());

        std::thread clientThread(&Server::send, &server, std::move(client));
        clientThread.detach();
    }

    return 0;
}
