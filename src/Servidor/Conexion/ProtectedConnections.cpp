#include "ProtectedConnections.h"

void ProtectedConnections::destroyFinishedClients() {
    std::lock_guard<std::mutex> lck (mutex);
    auto it = clients.begin();
    for ( ; it != clients.end(); ++it) {
        if((*it)->isDead()) {
            (*it)->joinResources();
            delete *it;
            clients.erase(it--);
        }
    }
}

void ProtectedConnections::destroyAllClients() {
    std::lock_guard<std::mutex> lck (mutex);
    auto it = clients.begin();
    for ( ; it != clients.end(); ++it) {
        (*it)->finish();
        (*it)->joinResources();
        delete *it;
        clients.erase(it--);
    }
}

void ProtectedConnections::push(ClientConnection* client) {
    std::lock_guard<std::mutex> lck (mutex);
    clients.push_back(client);
}

ProtectedConnections::ProtectedConnections() = default;

ProtectedConnections::~ProtectedConnections() = default;
