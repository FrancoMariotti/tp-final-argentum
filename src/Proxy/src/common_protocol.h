//
// Created by agustin on 1/6/20.
//

#ifndef TP3CLION_COMMON_PROTOCOL_H
#define TP3CLION_COMMON_PROTOCOL_H

#include <string>

class Socket;
class Protocol {
public:
    /*Envia el comando @param c por el socket
     * client side*/
    int send(Socket &socket, char c);

    /*Envia el @param number por el socket en formato bigEndian
     * client side*/
    int send(Socket &socket, uint16_t number);

    /*Recibe un uint32 por el socket con el largo del string,
     * lo pasa al endianess local y luego recibe por el socket un string*/
    std::string recieve(Socket &socket);

    /* Envia por el socket un uint32 con el largo del mensaje en formato
     * bigEndian y luego el msg @param.
     * server side*/
    int send(Socket &socket, const std::string &msg) const;

    /* Recibe un uint16 por el socket y lo pasa al endianess local*/
    uint16_t recieve(Socket &socket, int overload);

private:
    /*client side
     * Devuelve una copia de @param value en formato BigEndian*/
    uint16_t valueToBigEndian(uint16_t value) const;

    /*client side*/
    /*Devuelve una copia de @param value en endianess local*/
    uint32_t valueToLocalEndian(uint32_t value) const;

    /*server side*/
    uint16_t valueToLocalEndian(uint16_t value) const;

    /*server side*/
    uint32_t valueToBigEndian(uint32_t value) const;
};


#endif //TP3CLION_COMMON_PROTOCOL_H
