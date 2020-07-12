#ifndef ARGENTUM_THCLIENTRECEIVER_H
#define ARGENTUM_THCLIENTRECEIVER_H


#include <memory>
#include <Proxy/src/common_thread.h>
#include <Proxy/src/client_protected_list.h>
#include "Protocol.h"

class ClientConnection;
class ThClientReceiver: public Thread {
    std::string& id;
    bool keepTalking;
    Socket& client;
    Protocol protocol;
    ProtectedList<std::unique_ptr<Message>>& events;
    ClientConnection* connection;
public:
    ThClientReceiver(std::string& id,Socket& client,ProtectedList<std::unique_ptr<Message>>& events,
                                                                        ClientConnection* connection);
    void start() override;
    void run() override;
    void stop();

};


#endif //ARGENTUM_THCLIENTRECEIVER_H
