#include "ClientConnection.h"

ClientConnection::ClientConnection(int id,Socket client, ProtectedList<std::unique_ptr<Message>>& messages):
                                                id(id),client(std::move(client)),sender(this->client,events),
                                                receiver(this->client,messages,this),dead(false) {}

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

int ClientConnection::getId() {
    return this->id;
}

void ClientConnection::sendLoginReponse(int answer) {
    Protocol protocol;
    protocol.send(client,answer);
}

void ClientConnection::sendMessage(int messageId, std::string data) {
    events.push(event_t {messageId,data});
}

ClientConnection::~ClientConnection() {
    client.shutdown(SHUT_RDWR);
    client.close();
}
