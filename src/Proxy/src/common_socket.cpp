//
// Created by agustin on 23/5/20.
//

#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <utility>
#include "common_socket.h"
//#include "common_closedsocket_exception.h"
#include "common_osexception.h"

#define BACKLOG 10;
#define RECV_ERROR_MSG "al intentar intentar recibir datos"
#define SEND_ERROR_MSG "al intentar intentar enviar datos"


Socket::Socket() :
    sfd(-1)
    {}

Socket::Socket(int file_descriptor) :
        sfd(file_descriptor)
    {}

Socket::Socket(Socket &&other) noexcept {
    this->sfd = other.sfd;
    other.sfd = -1;
}



int Socket::bindAndListen(const char* service) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; //TCP
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_canonname = nullptr;
    hints.ai_addr = nullptr;
    hints.ai_next = nullptr;

    struct addrinfo *result;
    getaddrinfo(nullptr, service, &hints, &result);

    struct addrinfo *rp = result;

    bool success = false;
    while (!success && rp != nullptr){
        int socket_file_descriptor = socket(rp->ai_family, rp->ai_socktype,
                                            rp->ai_protocol);

        if (socket_file_descriptor == -1){
            throw OSError("No pudo crearse el socket, "
                          "file descriptor invalido, fd:%d",
                          socket_file_descriptor);
        }

        if (bind(socket_file_descriptor, rp->ai_addr, rp->ai_addrlen) == 0){
            success = true;
            int backlog = BACKLOG;
            listen(socket_file_descriptor, backlog);
            this->sfd = socket_file_descriptor;
        } else {
            rp = rp->ai_next;
            ::close(socket_file_descriptor);
        }
    }
    freeaddrinfo(result);
    if (!success){
        throw OSError("El socket no pudo bindearse al puerto %s", service);
    }
    return 0;
}


Socket Socket::accept() const {

    //Socket* nuevo = new Socket(acep_file_descriptor);
    int newsocket = ::accept(this->sfd,nullptr,nullptr);

    if (newsocket == -1){
        throw OSError("Error en el accept");
    }

    return std::move(Socket(newsocket));
}


int Socket::connect(const char *host_name, const char *service) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; //TCP
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    struct addrinfo *result;
    getaddrinfo(host_name, service, &hints, &result);

    struct addrinfo *rp = result;

    bool success = false;
    while (!success && rp != nullptr){
        int socket_file_descriptor = socket(rp->ai_family, rp->ai_socktype,
                                            rp->ai_protocol);

        if (socket_file_descriptor == -1){
            throw OSError("No pudo crearse el socket, "
                          "file descriptor invalido, "
                          "fd:%d", socket_file_descriptor);
        }

        if (::connect(socket_file_descriptor,
                rp->ai_addr, rp->ai_addrlen) != -1){
            success = true;
            this->sfd = socket_file_descriptor;
        } else {
            rp = rp->ai_next;
            ::close(socket_file_descriptor);
        }
    }

    freeaddrinfo(result);
    if (!success){
        throw OSError("El socket no pudo conectarse al host %s, "
                      "puerto %s", host_name, service);
    }
    return 0;
}

int Socket::send(const char* buffer, size_t length) const {
    size_t bytes_sent = 0;
    size_t total_bytes = 0;
    size_t buffer_len = 0;

    while (total_bytes < length) {
        buffer_len = length - total_bytes;

        bytes_sent = ::send(this->sfd, buffer + total_bytes,buffer_len,
                            MSG_NOSIGNAL);

        if (bytes_sent < 0) {
            throw OSError(SEND_ERROR_MSG);
        }

        total_bytes += bytes_sent;
    }

    return bytes_sent;
}

void Socket::recieve(char* buffer, size_t length) const {
    size_t bytes_received = 0;
    size_t total_bytes = 0;
    size_t buffer_len = 0;

    while ((length - total_bytes) != 0) {
        buffer_len = length - total_bytes;

        bytes_received = ::recv(this->sfd,buffer + total_bytes,buffer_len,0);

        if (bytes_received <= 0) {
            throw OSError(RECV_ERROR_MSG);
        }

        total_bytes += bytes_received;
    }
}

Socket::~Socket() {
    if (sfd >= 0){
        ::shutdown(this->sfd, SHUT_RDWR);
        ::close(this->sfd);
    }
}

int Socket::shutdown(const int channel) {
    if (sfd >= 0){
        ::shutdown(this->sfd, channel);
    }
    return  0;
}

int Socket::close(){
    if (sfd>=0){
        ::close((this->sfd));
    }
    return 0;
}

Socket &Socket::operator=(Socket &&other) noexcept {
    this->sfd = other.sfd;
    //other.sfd = -1;
    return *this;
}
