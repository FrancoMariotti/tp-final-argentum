//
// Created by agustin on 13/6/20.
//

#ifndef ARGENTUM_COMMON_PROXY_SOCKET_H
#define ARGENTUM_COMMON_PROXY_SOCKET_H


#include "common_blocking_queue.h"

class ProxySocket {
private:
    BlockingQueue<t_command> proxyClientSocket;
    BlockingQueue<t_command> proxyServerSocket;

public:
    int writeToServer(const t_command& msg);
    t_command readServer();
    int writeToClient(const t_command& msg);
    t_command readClient();
};


#endif //ARGENTUM_COMMON_PROXY_SOCKET_H
