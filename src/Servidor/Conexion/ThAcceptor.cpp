#include "ThAcceptor.h"


ThAcceptor::ThAcceptor(const std::string& service)  {
    this->keep_talking = true;
    this->acceptor.bindAndListen(service.c_str());
}

void ThAcceptor::destroyFinishedClients() {
    auto it = clientSenders.begin();
    for ( ; it != clientSenders.end(); ++it) {
        if((*it)->isDead()) {
            (*it)->join();
            delete *it;
            clients.erase(it);
        }
    }


    auto it = clientReceivers.begin();
    for ( ; it != clientReceivers.end(); ++it) {
        if((*it)->isDead()) {
            (*it)->join();
            delete *it;
            clients.erase(it);
        }
    }
}

void ThAcceptor::destroyAllClients() {
    auto itrSenders = clientSenders.begin();
    for ( ; itrSenders != clientSenders.end(); ++itrSenders) {
        (*itrSenders).join();
        //delete (*itrSenders);
    }

    auto itRecvs = clientReceivers.begin();
    for ( ; itRecvs != clientReceivers.end(); ++itRecvs) {
        (*itRecvs).join();
        //delete *it;
    }
}



void ThAcceptor::start() {
    Thread::start();
}

void ThAcceptor::run() {
    BlockingQueue<Message> messages;
    while (keep_talking) {
        Socket client = acceptor.accept();
        //ClientManager* manager = new ClientManager(numbers[i],client,server);
        //clients.push_back(manager);
        //manager->start();

        //Aca hay que pasarle la blocking queue.
        auto *sender = new ThClientSender(client,messages);
        ThClientReceiver *receiver = new ThClientReceiver(client,messages);

        destroyFinishedClients();
    }
    destroyAllClients();

}

void ThAcceptor::stop() {
    this->keep_talking = false;
    this->acceptor.shutdown(SHUT_RDWR);
}
