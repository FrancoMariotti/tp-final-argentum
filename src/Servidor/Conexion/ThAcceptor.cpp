#include "ThAcceptor.h"

ThAcceptor::ThAcceptor(const std::string &service, BlockingQueue<std::unique_ptr<Message>> &messages,
                       ProtectedList<std::unique_ptr<Message>> &events):messages(messages),events(events) {
    this->keep_talking = true;
    this->acceptor.bindAndListen(service.c_str());
}

void ThAcceptor::destroyFinishedClients() {
    auto itrSenders = clientSenders.begin();
    for ( ; itrSenders != clientSenders.end(); ++itrSenders) {
        if((*itrSenders)->isDead()) {
            (*itrSenders)->join();
            delete *itrSenders;
            clientSenders.erase(itrSenders);
        }
    }


    auto itrReceivers = clientReceivers.begin();
    for ( ; itrReceivers != clientReceivers.end(); ++itrReceivers) {
        if((*itrReceivers)->isDead()) {
            (*itrReceivers)->join();
            delete *itrReceivers;
            clientReceivers.erase(itrReceivers);
        }
    }
}

void ThAcceptor::destroyAllClients() {
    auto itrSenders = clientSenders.begin();
    for ( ; itrSenders != clientSenders.end(); ++itrSenders) {
        (*itrSenders)->join();
        delete (*itrSenders);
    }

    auto itRecvs = clientReceivers.begin();
    for ( ; itRecvs != clientReceivers.end(); ++itRecvs) {
        (*itRecvs)->join();
        delete *itrSenders;
    }
}

void ThAcceptor::start() {
    Thread::start();
}

void ThAcceptor::run() {
    while (keep_talking) {
        Socket client = acceptor.accept();

        auto *sender = new ThClientSender(client,messages);
        auto *receiver = new ThClientReceiver(client,events);

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


