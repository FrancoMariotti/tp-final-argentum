#include <iostream>
#include "client_command.h"
#include "common_proxy_socket.h"
#include "common_message.h"

void Use::operator()(BlockingQueue<std::unique_ptr<Message>>& clientEvents, int i) {
    t_command command = {"usar ",i, 0};
    clientEvents.push(std::unique_ptr<Message> (
            new UseItem(i)));

}

void Use::free() {
    delete this;
}
