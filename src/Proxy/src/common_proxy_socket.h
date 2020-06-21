//
// Created by agustin on 13/6/20.
//

#ifndef ARGENTUM_COMMON_PROXY_SOCKET_H
#define ARGENTUM_COMMON_PROXY_SOCKET_H

#include "common_blocking_queue.h"

class Message;
class ProxySocket {
private:
    BlockingQueue<std::unique_ptr<Message>> proxyClientSocket;
    BlockingQueue<std::unique_ptr<Message>> proxyServerSocket;

public:
    void writeToServer(std::unique_ptr<Message> msg);
    std::unique_ptr<Message> readServer();
    void writeToClient(std::unique_ptr<Message> msg);
    std::unique_ptr<Message> readClient();
    void shutdown();
};


#endif //ARGENTUM_COMMON_PROXY_SOCKET_H
