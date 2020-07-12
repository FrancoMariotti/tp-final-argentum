#ifndef ARGENTUM_PROTECTEDCONNECTIONS_H
#define ARGENTUM_PROTECTEDCONNECTIONS_H


#include <vector>
#include "ClientConnection.h"

typedef void (*callback)(void* client);

class ProtectedConnections {
    std::queue<int>newConnections;
    std::map<std::string,int>channelsTable;
    std::mutex mutex;
    std::vector<ClientConnection*> clients;
public:
    ProtectedConnections();
    void push(ClientConnection *client);
    void destroyFinishedClients();
    void destroyAllClients();
    void broadcast(Message *event);
    void sendMessage(const std::string& id, Message *event);
    ~ProtectedConnections();
};


#endif //ARGENTUM_PROTECTEDCONNECTIONS_H
