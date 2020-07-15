#ifndef ARGENTUM_THCLIENTRECEIVER_H
#define ARGENTUM_THCLIENTRECEIVER_H


#include <memory>
#include <Common/Thread.h>
#include <Proxy/src/client_protected_list.h>
#include "Protocol.h"

class ClientConnection;
class ThClientReceiver: public Thread {
    bool keepTalking;
    Socket& client;
    Protocol protocol;
    ProtectedList<std::unique_ptr<Message>>& events;
    ClientConnection* connection;
public:
    ThClientReceiver(Socket& client,ProtectedList<std::unique_ptr<Message>>& events,
                                                                        ClientConnection* connection);
    void start() override;
    void run() override;
    void stop();

};


#endif //ARGENTUM_THCLIENTRECEIVER_H
