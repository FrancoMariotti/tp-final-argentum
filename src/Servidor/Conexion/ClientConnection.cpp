#include "ClientConnection.h"

ClientConnection::ClientConnection(Socket client, ProtectedList<std::unique_ptr<Message>>& messages,
                                   BlockingQueue<std::unique_ptr<Message>>& events):
                             client(std::move(client)),sender(this->client,events),receiver(this->client,messages,this) {
    dead = true;
}

ClientConnection::ClientConnection(ClientConnection && connection) noexcept:
client(connection.client),sender(std::move(connection.sender)),receiver(std::move(connection.receiver))  {}

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