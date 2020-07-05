#ifndef ARGENTUM_PROTOCOL_H
#define ARGENTUM_PROTOCOL_H


#include <Proxy/src/common_message.h>
#include <Proxy/src/common_socket.h>

class Protocol {
public:
    uint16_t valueToBigEndian(uint16_t value);
    uint16_t valueToLocalEndian(uint16_t value);
    void send(Socket &socket, uint16_t number);
    void send(Socket& socket,Message* message);
    Message* recieve(Socket &socket);
    uint16_t recieve(Socket &socket, int overload);
};


#endif //ARGENTUM_PROTOCOL_H
