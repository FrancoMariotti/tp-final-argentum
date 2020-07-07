#ifndef ARGENTUM_THCLIENTSENDER_H
#define ARGENTUM_THCLIENTSENDER_H


#include <memory>
#include <Proxy/src/common_message.h>
#include <Proxy/src/common_blocking_queue.h>
#include <Proxy/src/common_thread.h>
#include "Protocol.h"

class ThClientSender: public Thread {
    bool keepTalking;
    Socket& client;
    BlockingQueue<std::unique_ptr<Message>> messages;
    Protocol protocol;
public:
    explicit ThClientSender(Socket& client);
    void start() override;
    void run() override;
    void stop();

    ThClientSender(ThClientSender&& sender);
};


#endif //ARGENTUM_THCLIENTSENDER_H
