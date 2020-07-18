#ifndef ARGENTUM_PROTOCOL_H
#define ARGENTUM_PROTOCOL_H

#include "MessageSerializer.h"
#include "Message.h"
#include "Socket.h"

class Protocol {
    MessageSerializer serializer;
    uint32_t valueToBigEndian(uint32_t value);
    uint32_t valueToLocalEndian(uint32_t value);
public:
    uint32_t recieve(Socket &socket, int overload);
    void send(Socket &socket, int number);
    void send(Socket &socket, std::string data);
    void send(Socket& socket,Message* message);
    Message* recieve(Socket &socket);
};


#endif //ARGENTUM_PROTOCOL_H
