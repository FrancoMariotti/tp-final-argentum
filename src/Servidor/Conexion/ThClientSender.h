#ifndef ARGENTUM_THCLIENTSENDER_H
#define ARGENTUM_THCLIENTSENDER_H

#include <Proxy/src/common_thread.h>
#include <Proxy/src/common_socket.h>
#include <Proxy/src/common_message.h>
#include "Proxy/src/common_blocking_queue.h"

class ThClientSender: public Thread {
    bool keepTalking;
    Socket client;
    BlockingQueue<Message*>& messages;
public:
    ThClientSender(Socket client,BlockingQueue<Message*>& messages);
    void start() override;
    void run() override;
    void stop();
};


#endif //ARGENTUM_THCLIENTSENDER_H
