#include "ProtectedConnections.h"
#include "mutex"

ProtectedConnections::ProtectedConnections() = default;

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

void ProtectedConnections::sendMessage(const std::string& id,Message *event) {
    std::lock_guard<std::mutex> lck (mutex);
    for(auto& client:clients) {
        if(client->getId() == id) {
            client->sendMessage(event);
        }
    }
}

void ProtectedConnections::broadcast(Message *event) {
    std::lock_guard<std::mutex> lck (mutex);
    for(auto& client:clients) {
        client->sendMessage(event);
    }
}

void ProtectedConnections::push(ClientConnection* client) {
    std::lock_guard<std::mutex> lck (mutex);
    clients.push_back(client);
}

ProtectedConnections::~ProtectedConnections() = default;
