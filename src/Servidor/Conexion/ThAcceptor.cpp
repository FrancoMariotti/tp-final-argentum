#include <algorithm>
#include <Proxy/src/common_socket.h>
#include "ThAcceptor.h"
#include "ClientConnection.h"
#include "vector"

ThAcceptor::ThAcceptor(const std::string &service, BlockingQueue<std::unique_ptr<Message>> &messages,
                       ProtectedList<std::unique_ptr<Message>> &events):messages(messages),events(events) {
    this->keepTalking= true;
    this->acceptor.bindAndListen(service.c_str());
}

void ThAcceptor::destroyFinishedClients() {
    std::vector<ClientConnection*>::iterator itrClients = clients.begin();
    for ( ; itrClients != clients.end(); ++itrClients) {
        if((*itrClients)->isDead()) {
            (*itrClients)->joinResources();
        }
    }
    clients.erase(std::remove_if(clients.begin(),
                                 clients.end(),
                                 [](ClientConnection *connection){return connection->isDead();}),
                                         clients.end());
}

void ThAcceptor::destroyAllClients() {
    auto itrClients = clients.begin();
    for ( ; itrClients != clients.end(); ++itrClients) {
        (*itrClients)->finish();
        (*itrClients)->joinResources();
    }

    clients.erase(std::remove_if(clients.begin(),
                                 clients.end(),
                                 [](ClientConnection *connection){return connection->isDead();}),
                  clients.end());
}

void ThAcceptor::start() {
    Thread::start();
}

void ThAcceptor::run() {
    while (keepTalking) {
        try {
            Socket* client = new Socket();
            *client = acceptor.accept();
            auto *connection = new ClientConnection(client, events, messages);
            connection->start();
            clients.push_back(connection);
            destroyFinishedClients();
        } catch(std::exception &e) {
            stop();
        }
    }

    destroyAllClients();
}

void ThAcceptor::stop() {
    this->keepTalking = false;
    this->acceptor.shutdown(SHUT_RDWR);
}

ThAcceptor::~ThAcceptor() {
    auto itr = clients.begin();
    for (;itr!= clients.end();itr++) {
        delete *itr;
    }
}

