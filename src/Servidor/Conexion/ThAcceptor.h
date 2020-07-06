#ifndef ARGENTUM_THACCEPTOR_H
#define ARGENTUM_THACCEPTOR_H

#include "vector"
#include <Proxy/src/common_thread.h>
#include <Proxy/src/common_socket.h>
#include <Proxy/src/common_blocking_queue.h>
#include <Proxy/src/client_protected_list.h>
#include <Proxy/src/common_message.h>

class ClientConnection;

class ThAcceptor: public Thread {
    Socket acceptor;
    std::vector<ClientConnection*> clients;
    BlockingQueue<std::unique_ptr<Message>>& messages;
    ProtectedList<std::unique_ptr<Message>>& events;
    bool keepTalking;
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
