#ifndef ARGENTUM_THCLIENTRECEIVER_H
#define ARGENTUM_THCLIENTRECEIVER_H


#include <Proxy/src/common_thread.h>
#include <Proxy/src/common_socket.h>
#include <Proxy/src/common_message.h>
#include <Proxy/src/common_blocking_queue.h>
#include "Proxy/src/client_protected_list.h"

class ThClientReceiver: public Thread {
    bool keepTalking;
    Socket client;
    ProtectedList<std::unique_ptr<Message>>& events;
public:
    ThClientReceiver(Socket client,ProtectedList<std::unique_ptr<Message>>& events);
    void start() override ;
    void run() override ;
    void stop();

};


#endif //ARGENTUM_THCLIENTRECEIVER_H
