//
// Created by agustin on 23/5/20.
//

#ifndef TP3CLION_COMMON_SOCKET_H
#define TP3CLION_COMMON_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string>
#include <iostream>

class Socket {
private:
    int sfd;

public:
    Socket();

    Socket(const Socket&) = default;

    Socket(Socket&& other) noexcept;
    Socket& operator=(Socket&& other) noexcept;
    Socket& operator=(const Socket&) = delete;
    /* Asigna una direccion al socket del servidor y
    lo pone a la espera de una conexion
    */
    int bindAndListen(const char *service);

    /*Espera a que se conecte un cliente y retorna
     * un nuevo socket
    */
    Socket accept() const;

    /* Se conecta a un servidor dada una dirección y un servicio
    */
    int connect(const char* host_name, const char* service);

    /* Envia cantidad length de bytes a traves del socket.
    Devuelve la cantidad de bytes que se enviaron, 0 si el socket se cerro
    o -1 si hubo un error.
    */
    int send(const char *buffer, size_t length) const;

    /* Recibe cantidad length de bytes a traves del socket.
    Devuelve la cantidad de bytes que se recibieron, 0 si el socket se cerro
    o -1 si hubo un error.*/
    void recieve(char* buffer, size_t length) const;

    /*Cierra el canal de comunicacion
    */
    int shutdown(int channel);

    int close();

    ~Socket();
private:

    explicit Socket(int file_descriptor);
};

#endif //TP3CLION_COMMON_SOCKET_H
