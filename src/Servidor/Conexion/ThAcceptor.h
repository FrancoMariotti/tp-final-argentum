#ifndef ARGENTUM_THACCEPTOR_H
#define ARGENTUM_THACCEPTOR_H

#include <Proxy/src/common_thread.h>
#include <Proxy/src/common_socket.h>

class ThAcceptor: public Thread {
    Socket acceptor;
    bool keep_talking;
public:
    ThAcceptor(const std::string& service);
    void start() override;
    void run() override;
    void stop();
    void destroyFinishedClients();
    void destroyAllClients();
};


#endif //ARGENTUM_THACCEPTOR_H
