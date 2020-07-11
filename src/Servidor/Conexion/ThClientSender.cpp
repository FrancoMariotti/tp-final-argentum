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
    try {
        //protocol.send(client,1);//aca deberia mandarle el id al cliente.
        Message* message;
        while(keepTalking) {

            std::cout << "sending event" << std::endl;
            message = messages.pop();
            protocol.send(client,message);
            delete message;
        }
    } catch(std::exception &e) {
        keepTalking = false;
    }
}

void ThClientSender::stop() {
    messages.close();
}