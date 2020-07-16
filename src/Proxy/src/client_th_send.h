//
// Created by agustin on 19/6/20.
//

#ifndef ARGENTUM_CLIENT_TH_SEND_H
#define ARGENTUM_CLIENT_TH_SEND_H

#include "Common/BlockingQueue.h"
#include "Common/Thread.h"
#include "Common/Socket.h"
#include "Common/Protocol.h"

class Message;
class ProxySocket;
class ThSend : public Thread{
private:
    /*Recurso compartido con el cliente*/
    BlockingQueue<std::unique_ptr<Message>>& clientEvents;
    /**Conoce el protocolo, pero por ahora solo conoce al proxySocket*/
    //Protocol protocol;
    Socket& socket;
    Protocol protocol;

    bool keep_sending;
public:
    ThSend(BlockingQueue<std::unique_ptr<Message>> &clientEvents, Socket &socket);

    ThSend(const ThSend& other) = delete;

    ThSend(ThSend&& other) noexcept ;

    void run() override ;

    void stop();

    ~ThSend() override;


};


#endif //ARGENTUM_CLIENT_TH_SEND_H
