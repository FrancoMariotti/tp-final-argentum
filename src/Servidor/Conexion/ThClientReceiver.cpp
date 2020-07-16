#include "ThClientReceiver.h"
#include "ClientConnection.h"
#include <Common/ClosedQueueException.h>

ThClientReceiver::ThClientReceiver(Socket& client, ProtectedList<std::unique_ptr<Message>> &events,
        ClientConnection* connection):client(client),events(events),connection(connection) {
    this->keepTalking = true;
}

void ThClientReceiver::start() {
    Thread::start();
}

void ThClientReceiver::run() {
    while (keepTalking) {
        try{
            //std::cout << "recieving event" << std::endl;
            Message* message = protocol.recieve(client);
            if(message) {
                message->setConnectionlId(connection->getId());
                events.push(std::unique_ptr<Message>(message));
            }

        } catch(std::exception &e) {
            std::cout << e.what() <<std::endl;
            keepTalking = false;
        }
    }
    connection->stop();
}

void ThClientReceiver::stop() {
    keepTalking = false;
}
