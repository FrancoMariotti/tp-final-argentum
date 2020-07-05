//
// Created by franco on 5/7/20.
//

#include "ThAcceptor.h"


ThAcceptor::ThAcceptor(const std::string& service)  {
    this->keep_talking = true;
    this->acceptor.bindAndListen(service.c_str());
}

void ThAcceptor::destroyFinishedClients() {
    /*auto it = clients.begin();
    for ( ; it != clients.end(); ++it) {
        if((*it)->isDead()) {
            (*it)->join();
            delete *it;
            clients.erase(it);
        }
    }*/
}

void ThAcceptor::destroyAllClients() {
    /*auto it = clients.begin();
    for ( ; it != clients.end(); ++it) {
        (*it)->join();
        delete *it;
    }*/
}



void ThAcceptor::start() {
    Thread::start();
}

void ThAcceptor::run() {

}

void ThAcceptor::stop() {
    this->keep_talking = false;
    this->acceptor.shutdown(SHUT_RDWR);
}
