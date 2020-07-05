#include <cstring>
#include "Protocol.h"

uint16_t Protocol::valueToBigEndian(const uint16_t value) {
    uint16_t big_end = htons(value);
    return big_end;
}

int Protocol::send(Socket &socket, uint16_t number){
    uint16_t big_end_guest = valueToBigEndian(number);
    socket.send(&big_end_guest, sizeof(uint16_t));
    return 0;
}

void Protocol::send(Socket &socket, Message *message) {
    /*logica de protocolo*/
    //primero se envia el id del mensaje
    send(socket,message->getId());
    //serializamos el mensaje
    const char* data = message.serialize();
    uint16_t lenData = strlen(data);
    //enviamos el size del chunck de bytes que vamos a enviar.
    send(socket,lenData);
    //enviamos el chunck de bytes.
    socket.send(data,lenData);
}

Message *Protocol::receive(Socket &socket) {
    return nullptr;
}
