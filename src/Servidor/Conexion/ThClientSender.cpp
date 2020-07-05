#include "ThClientSender.h"

ThClientSender::ThClientSender(Socket client,BlockingQueue<Message>& messages):client(std::move(client)),messages(messages) {
}

void ThClientSender::start() {
    Thread::start();
}

void ThClientSender::run() {

}

void ThClientSender::stop() {
     keep_talking = false;
    client.shutdown(SHUT_WR);
}
