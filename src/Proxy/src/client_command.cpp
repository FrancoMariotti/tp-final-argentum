#include <iostream>
#include "client_command.h"
#include "common_proxy_socket.h"

void Use::operator()(BlockingQueue<t_command> &event_sender, int i) {
    t_command command = {"usar ",i, 0};
    event_sender.push(command);
}

void Use::free() {
    delete this;
}
