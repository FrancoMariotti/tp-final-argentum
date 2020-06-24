//
// Created by franco on 16/6/20.
//

#ifndef ARGENTUM_UPDATE_H
#define ARGENTUM_UPDATE_H


#include <Proxy/src/common_proxy_socket.h>
#include "Offset.h"

class Update {
    int x;
    int y;
    public:
        Update(Offset& offset);
        void send(ProxySocket &socket);
};


#endif //ARGENTUM_UPDATE_H
