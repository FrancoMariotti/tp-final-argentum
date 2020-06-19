//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_CLIENT_TH_SEND_H
#define ARGENTUM_CLIENT_TH_SEND_H

#include "common_blocking_queue.h"
#include "common_thread.h"

class ProxySocket;
class ThSend : public Thread{
private:
    /*Recurso compartido con el cliente*/
    BlockingQueue<t_command>& clientEvents;
    /**Conoce el protocolo, pero por ahora conoce al proxySocket*/
    //Protocol protocol;
    ProxySocket& proxySocket;

    bool keep_sending;
public:
    ThSend(BlockingQueue<t_command> &clientEvents, ProxySocket &proxySocket);

    ThSend(const ThSend& other) = delete;

    ThSend(ThSend&& other) noexcept ;

    void run() override ;

    ~ThSend() override;


};


#endif //ARGENTUM_CLIENT_TH_SEND_H
