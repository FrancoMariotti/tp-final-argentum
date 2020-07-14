#include "Protocol.h"
#include "Common/Message.h"

uint16_t Protocol::valueToBigEndian(const uint16_t value) {
    uint16_t big_end = htons(value);
    return big_end;
}

uint16_t Protocol::valueToLocalEndian(uint16_t value) {
    uint16_t local_end = ntohs(value);
    return local_end;
}

void Protocol::send(Socket &socket, uint16_t number){
    uint16_t big_end_guest = valueToBigEndian(number);
    socket.send(&big_end_guest, sizeof(uint16_t));
}

uint16_t Protocol::recieve(Socket &socket, int overload){
    uint16_t number;
    socket.receive((char*)&number, sizeof(uint16_t));
    number = valueToLocalEndian(number);
    return number;
}

void Protocol::send(Socket& socket,Message* message) {
    send(socket,message->getId());
    std::string data = serializer.serialize(message);
    send(socket,data.size());
    socket.send(data.data(),data.size());
}

Message* Protocol::recieve(Socket &socket) {
    uint16_t messageId = recieve(socket,0);
    uint16_t len_data = recieve(socket,0);
    char* data  = (char*) malloc(len_data+1);
    memset(data,0,len_data);
    data[len_data] = '\0';
    socket.receive(data,len_data);
    Message *message = serializer.deserialize(messageId,(unsigned char*)data,len_data);
    free(data);
    return message;
}

