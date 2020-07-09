#include "ThClientSender.h"
#include <memory>
ThClientSender::ThClientSender(Socket& client,BlockingQueue<Message*>& messages):
                                                                client(client),messages(messages) {
    this->keepTalking = true;
}

void ThClientSender::start() {
    Thread::start();
}

void ThClientSender::run() {
    Message* message;
    while(keepTalking) {
        try {
            std::cout << "sending event" << std::endl;
            message = messages.pop();
            protocol.send(client,message);
            delete message;
        } catch(std::exception &e) {
            keepTalking = false;
        }
    }
}

void ThClientSender::stop() {
    messages.close();
}