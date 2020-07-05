#include "ThAcceptor.h"


ThAcceptor::ThAcceptor(const std::string& service)  {
    this->keep_talking = true;
    this->acceptor.bindAndListen(service.c_str());
}

void ThAcceptor::destroyFinishedClients() {
    auto itrSenders = clientSenders.begin();
    for ( ; itrSenders != clientSenders.end(); ++itrSenders) {
        if((*itrSenders).isDead()) {
            (*itrSenders)->join();
            //delete *it;
            clientSenders.erase(itrSenders);
        }
    }


    auto itrReceivers = clientReceivers.begin();
    for ( ; itrReceivers != clientReceivers.end(); ++itrReceivers) {
        if((*itrReceivers)->isDead()) {
            (*itrReceivers)->join();
            //delete *it;
            clientReceivers.erase(itrReceivers);
        }
    }
}

void ThAcceptor::destroyAllClients() {
    auto itrSenders = clientSenders.begin();
    for ( ; itrSenders != clientSenders.end(); ++itrSenders) {
        (*itrSenders)->join();
        //delete (*itrSenders);
    }

    auto itRecvs = clientReceivers.begin();
    for ( ; itRecvs != clientReceivers.end(); ++itRecvs) {
        (*itRecvs)->join();
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
        auto *receiver = new ThClientReceiver(client,messages);

        clientSenders.push_back(sender);
        clientReceivers.push_back(receiver);


        destroyFinishedClients();
    }
    destroyAllClients();

}

void ThAcceptor::stop() {
    this->keep_talking = false;
    this->acceptor.shutdown(SHUT_RDWR);
}
