#ifndef ARGENTUM_PROTOCOL_H
#define ARGENTUM_PROTOCOL_H


#include <Proxy/src/common_message.h>
#include <Proxy/src/common_socket.h>

class Protocol {
public:
    void send(Socket& socket,Message* message);
    Message* receive(Socket& socket);

    uint16_t valueToBigEndian(const uint16_t value);

    int send(Socket &socket, uint16_t number);
};


#endif //ARGENTUM_PROTOCOL_H
