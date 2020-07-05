#include "ThClientReceiver.h"
#include <utility>

ThClientReceiver::ThClientReceiver(Socket client, ProtectedList<std::unique_ptr<Message>> &events):
                                    client(std::move(client)),events(events) {
    keepTalking = true;
}

void ThClientReceiver::start() {
    Thread::start();
}

void ThClientReceiver::run() {
    while (keepTalking) {
        try{
            std::cout << "recieving event" << std::endl;
            Message* message = protocol.recieve(client);
            events.push(std::unique_ptr<Message>(message));
        } catch ( ClosedQueueException &e){
            stop();
        }
    }
    finished = true;
}

void ThClientReceiver::stop() {
    keepTalking = false;
    client.shutdown(SHUT_RD);
}
