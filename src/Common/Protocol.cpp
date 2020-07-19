#include "Protocol.h"
#include "Messages/Message.h"

uint32_t Protocol::valueToBigEndian(const uint32_t value) {
    return htonl(value);
}

uint32_t Protocol::valueToLocalEndian(uint32_t value) {
    return ntohl(value);
}

uint32_t Protocol::recieve(Socket &socket, int overload){
    uint32_t number;
    socket.receive((char*)&number, sizeof(uint32_t));
    number = valueToLocalEndian(number);
    return number;
}

void Protocol::send(Socket &socket, int number) {
    uint32_t big_end_guest = valueToBigEndian(number);
    socket.send(&big_end_guest, sizeof(uint32_t));
}

void Protocol::send(Socket &socket, std::string data) {
    send(socket,data.size());
    socket.send(data.data(),data.size());
}

void Protocol::send(Socket& socket,Message* message) {
    send(socket,message->getId());
    std::string data = serializer.serialize(message);
    send(socket,data);
}

Message* Protocol::recieve(Socket &socket) {
    uint32_t messageId = recieve(socket,0);
    uint32_t len_data = recieve(socket,0);
    char* data  = (char*) malloc(len_data+1);
    memset(data,0,len_data);
    data[len_data] = '\0';
    socket.receive(data,len_data);
    Message *message = serializer.deserialize(messageId,(unsigned char*)data,len_data);
    free(data);
    return message;
}

