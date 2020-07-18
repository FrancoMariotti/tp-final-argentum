#include "ThClientSender.h"
#include <memory>
ThClientSender::ThClientSender(Socket& client,BlockingQueue<event_t>& messages):
                                                                client(client),messages(messages) {
    this->keepTalking = true;
}

void ThClientSender::start() {
    Thread::start();
}

void ThClientSender::run() {
    try {
        while(keepTalking) {
            std::cout << "sending event" << std::endl;
            event_t  event= messages.pop();
            protocol.send(client,event.id);
            if(event.data.size() > 0) {
                protocol.send(client,event.data);
            }
        }
    } catch(std::exception &e) {
        keepTalking = false;
    }
}

void ThClientSender::stop() {
    messages.close();
}