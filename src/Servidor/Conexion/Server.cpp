#include "Server.h"

#define END_SIGNAL 'c'

Server::Server(std::string service):clientAcceptor(service,messages,events) {}

void Server::start() {

    this->clientAcceptor.start();

    char input = 0;
    while (input != END_SIGNAL){
        std::cin >> input;
    }
    clientAcceptor.stop();
    clientAcceptor.join();
}
