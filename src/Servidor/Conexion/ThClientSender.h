#ifndef ARGENTUM_THCLIENTSENDER_H
#define ARGENTUM_THCLIENTSENDER_H


#include <memory>
#include <Common/Message.h>
#include <Common/BlockingQueue.h>
#include <Common/Thread.h>
#include "Protocol.h"

class ThClientSender: public Thread {
    bool keepTalking;
    Socket& client;
    BlockingQueue<Message*>& messages;
    Protocol protocol;
public:
    explicit ThClientSender(Socket& client,BlockingQueue<Message*>& messages);
    void start() override;
    void run() override;
    void stop();
};


#endif //ARGENTUM_THCLIENTSENDER_H
