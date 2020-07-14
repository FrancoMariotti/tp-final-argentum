#include "ThClientReceiver.h"
#include "ClientConnection.h"
#include <Common/ClosedQueueException.h>

ThClientReceiver::ThClientReceiver(std::string& id,Socket& client, ProtectedList<std::unique_ptr<Message>> &events,
        ClientConnection* connection):id(id),client(client),events(events),connection(connection) {
    this->keepTalking = true;
}

void ThClientReceiver::start() {
    Thread::start();
}

void ThClientReceiver::run() {
    while (keepTalking) {
        try{
            std::cout << "recieving event" << std::endl;
            Message* message = protocol.recieve(client);
            if(message) {
                if(message->getId() == CONNECT_MESSAGE_ID) {
                    id = message->getConnectData().username;
                }
                events.push(std::unique_ptr<Message>(message));
            }

        } catch(std::exception &e) {
            keepTalking = false;
        }
    }
    connection->stop();
}

void ThClientReceiver::stop() {
    keepTalking = false;
}
