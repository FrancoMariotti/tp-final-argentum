#include "ProtectedConnections.h"

#include <utility>
#include "mutex"

ProtectedConnections::ProtectedConnections() = default;

void ProtectedConnections::destroyFinishedClients() {
    std::lock_guard<std::mutex> lck (mutex);
    auto it = clients.begin();
    for ( ; it != clients.end(); ++it) {
        if((*it)->isDead()) {
            (*it)->joinResources();
            delete *it;
            clients.erase(it);
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
    }
    clients.clear();
}

void ProtectedConnections::push(ClientConnection* client) {
    std::lock_guard<std::mutex> lck (mutex);
    clients.push_back(client);
}

void ProtectedConnections::sendMessage(int connectionId,int answer) {
    std::lock_guard<std::mutex> lck (mutex);
    for(auto& client:clients) {
        if(client->getId() == connectionId) {
            client->sendLoginReponse(answer);
            break;
        }
    }
}


void ProtectedConnections::sendMessage(int connectionId,int messageId,std::string data) {
    std::lock_guard<std::mutex> lck (mutex);
    for(auto& client:clients) {
        if(client->getId() == connectionId) {
            client->sendMessage(messageId,data);
            break;
        }
    }
}

void ProtectedConnections::broadcast(int messageId,std::string data) {
    std::lock_guard<std::mutex> lck (mutex);
    for(auto& client:clients) {
        client->sendMessage(messageId,data);
    }
}

ProtectedConnections::~ProtectedConnections() = default;
