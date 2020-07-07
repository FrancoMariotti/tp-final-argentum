#include "ClientConnection.h"

ClientConnection::ClientConnection(Socket client, ProtectedList<std::unique_ptr<Message>>& messages):
                             client(std::move(client)),sender(this->client),receiver(this->client,messages,this) {
    dead = true;
}

void ClientConnection::joinResources() {
    receiver.join();
    sender.join();
}

void ClientConnection::finish() {
    receiver.stop();
}

void ClientConnection::stop() {
    dead = true;
    sender.stop();
}

bool ClientConnection::isDead() const {
    return dead;
}

void ClientConnection::start() {
    receiver.start();
    sender.start();
}

ClientConnection::~ClientConnection() {
    client.shutdown(SHUT_RDWR);
    client.close();
}
