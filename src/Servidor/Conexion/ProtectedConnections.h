#ifndef ARGENTUM_PROTECTEDCONNECTIONS_H
#define ARGENTUM_PROTECTEDCONNECTIONS_H


#include <vector>
#include "ClientConnection.h"

typedef void (*callback)(void* client);

class ProtectedConnections {
    std::mutex mutex;
    std::vector<ClientConnection*> clients;
public:
    ProtectedConnections();
    void push(ClientConnection *client);
    void destroyFinishedClients();
    void destroyAllClients();
    void broadcast(int messageId,std::string data);
    void sendMessage(int connectionId,int messageId,std::string data);
    ~ProtectedConnections();
};


#endif //ARGENTUM_PROTECTEDCONNECTIONS_H
