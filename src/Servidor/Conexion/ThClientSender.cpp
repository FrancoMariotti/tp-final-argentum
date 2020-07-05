#include "ThClientSender.h"

ThClientSender::ThClientSender(Socket client,BlockingQueue<Message*>& messages):client(std::move(client)),messages(messages) {
    this->keepTalking = true;
}

void ThClientSender::start() {
    Thread::start();
}

void ThClientSender::run() {
    Message *message;
    while(keepTalking) {
        try {
            message = messages.pop();
            //si falla el send se lanza una excepcion
            protocol.send(client,message);
        } catch(std::exception &e) {
            printf("%s", e.what());
            stop();
        }
    }

}

void ThClientSender::stop() {
    keepTalking = false;
    client.shutdown(SHUT_WR);
}
