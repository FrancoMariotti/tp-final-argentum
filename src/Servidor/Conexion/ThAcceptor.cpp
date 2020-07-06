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
    auto it = clients.begin();
    for ( ; it != clients.end(); ++it) {
        if((*it)->isDead()) {
            (*it)->joinResources();
            delete *it;
            clients.erase(it--);
        }
    }
}

void ThAcceptor::destroyAllClients() {
    auto it = clients.begin();
    for ( ; it != clients.end(); ++it) {
        (*it)->finish();
        (*it)->joinResources();
        delete *it;
        clients.erase(it--);
    }
}

void ThAcceptor::start() {
    Thread::start();
}

void ThAcceptor::run() {
    while (keepTalking) {
        try {
            Socket client = acceptor.accept();
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
    for (;itr!= clients.end();++itr) {
        delete *itr;
    }
}

