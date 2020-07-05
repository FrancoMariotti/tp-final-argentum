#ifndef ARGENTUM_THCLIENTSENDER_H
#define ARGENTUM_THCLIENTSENDER_H

#include <Proxy/src/common_thread.h>
#include <Proxy/src/common_socket.h>
#include <Proxy/src/common_message.h>
#include "Proxy/src/common_blocking_queue.h"
#include "Protocol.h"

class ThClientSender: public Thread {
    bool keepTalking;
    Socket client;
    BlockingQueue<std::unique_ptr<Message>>& messages;
    Protocol protocol;
public:
    ThClientSender(Socket client,BlockingQueue<std::unique_ptr<Message>>& messages);
    void start() override;
    void run() override;
    void stop();
};


#endif //ARGENTUM_THCLIENTSENDER_H
