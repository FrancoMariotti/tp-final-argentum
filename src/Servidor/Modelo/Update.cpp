//
// Created by franco on 16/6/20.
//

#include <Proxy/src/common_message.h>
#include "Update.h"

Update::Update(Offset &offset) {
    this->x = offset.getX();
    this->y = offset.getY();
}

void Update::send(ProxySocket &socket) {
    socket.writeToClient(std::unique_ptr<Message> (
            new Movement(x*5,y*5)));
}
