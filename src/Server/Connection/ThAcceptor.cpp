#include <Common/Socket.h>
#include "ThAcceptor.h"
#include "ClientConnection.h"
#include "vector"
#include "ProtectedConnections.h"

ThAcceptor::ThAcceptor(const std::string &service,ProtectedConnections& clients,
                       ProtectedList<std::unique_ptr<Message>> &events):clients(clients),events(events) {
    this->counter = 0;
    this->keepTalking = true;
    this->acceptor.bindAndListen(service.c_str());
}

void ThAcceptor::start() {
    Thread::start();
}

void ThAcceptor::run() {
    while (keepTalking) {
        try {
            Socket client = acceptor.accept();
            auto *connection = new ClientConnection(counter,std::move(client), events);
            connection->start();
            clients.push(connection);
            clients.destroyFinishedClients();
            counter++;
        } catch(std::exception &e) {
            stop();
        }
    }

    clients.destroyAllClients();
}

void ThAcceptor::stop() {
    this->keepTalking = false;
    this->acceptor.shutdown(SHUT_RDWR);
}

ThAcceptor::~ThAcceptor() = default;
