#ifndef ARGENTUM_THACCEPTOR_H
#define ARGENTUM_THACCEPTOR_H

#include <Proxy/src/common_thread.h>
#include <Proxy/src/common_socket.h>
#include "ThClientReceiver.h"
#include "ThClientSender.h"

class ThAcceptor: public Thread {
    Socket acceptor;
    std::vector<ThClientReceiver*> clientReceivers;
    std::vector<ThClientSender*> clientSenders;
    BlockingQueue<std::unique_ptr<Message>>& messages;
    ProtectedList<std::unique_ptr<Message>>& events;
    bool keep_talking;
public:
    ThAcceptor(const std::string& service, BlockingQueue<std::unique_ptr<Message>>& messages,
    ProtectedList<std::unique_ptr<Message>>& events);
    void start() override;
    void run() override;
    void stop();
    void destroyFinishedClients();
    void destroyAllClients();
};


#endif //ARGENTUM_THACCEPTOR_H
