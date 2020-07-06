#include "ThClientSender.h"
#include <memory>
ThClientSender::ThClientSender(Socket& client,BlockingQueue<std::unique_ptr<Message>>& messages):
                                client(client),messages(messages) {
    this->keepTalking = true;
}

void ThClientSender::start() {
    Thread::start();
}

void ThClientSender::run() {
    std::unique_ptr<Message> message;
    while(keepTalking) {
        try {
            std::cout << "sending event" << std::endl;
            message = messages.pop();
            protocol.send(client,message.release());
        } catch(std::exception &e) {
            stop();
        }
    }
    finished = true;
}

void ThClientSender::stop() {
    keepTalking = false;
    //client.shutdown(SHUT_WR);
}
