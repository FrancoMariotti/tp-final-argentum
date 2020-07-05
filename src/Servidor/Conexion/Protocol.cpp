#include <cstring>
#include "Protocol.h"

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
    socket.recieve(&number, sizeof(uint16_t));
    number = valueToLocalEndian(number);
    return number;
}

void Protocol::send(Socket& socket,Message* message) {
    /*logica de protocolo*/
    //primero se envia el id del mensaje
    send(socket,message->getId());
    //serializamos el mensaje
    const char* data = message->serialize();
    uint16_t lenData = strlen(data);
    //enviamos el size del chunck de bytes que vamos a enviar.
    send(socket,lenData);
    //enviamos el chunck de bytes.
    socket.send(data,lenData);
}

Message* Protocol::recieve(Socket &socket) {
    uint16_t messageId = recieve(socket, 0);
    uint16_t len_data = recieve(socket,0);
    char* data  = (char*) malloc(len_data);
    socket.recieve(data,len_data);
    Message *message = message->deserialize(data);
    delete data;
    return message;
}

