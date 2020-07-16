#ifndef ARGENTUM_THCLIENTSENDER_H
#define ARGENTUM_THCLIENTSENDER_H


#include <memory>
#include <Common/Message.h>
#include <Common/BlockingQueue.h>
#include <Common/Thread.h>
#include "Common/Protocol.h"

typedef struct event {
    int id;
    std::string data;
} event_t;

class ThClientSender: public Thread {
    bool keepTalking;
    Socket& client;
    BlockingQueue<event_t>& messages;
    Protocol protocol;
public:
    explicit ThClientSender(Socket& client,BlockingQueue<event_t>& messages);
    void start() override;
    void run() override;
    void stop();
};


#endif //ARGENTUM_THCLIENTSENDER_H
