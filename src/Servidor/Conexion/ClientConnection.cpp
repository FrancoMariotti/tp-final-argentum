#include "ClientConnection.h"

ClientConnection::ClientConnection(Socket client, ProtectedList<std::unique_ptr<Message>>& messages):
                                                client(std::move(client)),sender(this->client,events),
                                                receiver(id,this->client,messages,this),dead(false) {}

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

void ClientConnection::sendMessage(Message* event) {
    events.push(event);
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

std::string ClientConnection::getId() {
    return this->id;
}
