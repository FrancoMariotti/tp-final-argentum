//
// Created by agustin on 20/6/20.
//

#ifndef ARGENTUM_CLIENT_TH_RECV_H
#define ARGENTUM_CLIENT_TH_RECV_H

#include "client_protected_list.h"
#include "common_thread.h"

class Message;
class ProxySocket;
class ThRecv : public Thread {
private:
    ProtectedList<std::unique_ptr<Message>>& serverEvents;
    /**Protocol*/
    ProxySocket& proxySocket;
    bool keep_recieving;

public:
    ThRecv(ProtectedList<std::unique_ptr<Message>> &serverEvents, ProxySocket &proxySocket);

    ThRecv(const ThRecv& other) = delete;

    ThRecv(ThRecv&& other) noexcept ;

    void run() override ;

    ~ThRecv() override;


    void stop();
};


#endif //ARGENTUM_CLIENT_TH_RECV_H
