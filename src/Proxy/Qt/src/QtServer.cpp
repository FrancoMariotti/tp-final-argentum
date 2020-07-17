//
// Created by agustin on 15/7/20.
//

#include "QtServer.h"
#include <thread>

#define CLOSE_SERVER 'q'
#define LOGIN_COMMAND 'l'
#define SIGNUP_COMMAND 's'
#define CREATE_COMMAND 'c'
#define USER_EXISTS 1

QtServer::QtServer(const char *service) :
    acep_socket(),
    keep_talking(true){
    acep_socket.bindAndListen(service);
}

void QtServer::operator()(){
    std::thread acep_th(&QtServer::start, this);
    char c = std::cin.get();
    while (c != CLOSE_SERVER){
        c = std::cin.get();
    }
    keep_talking = false;
    acep_socket.shutdown(SHUT_RDWR);
    acep_th.join();

}

void QtServer::start(){
    try{
        Socket peer = acep_socket.accept();
        while(keep_talking){
            char c_cmd;
            peer.recieve(&c_cmd, sizeof(char));
            if (c_cmd == LOGIN_COMMAND){
                char c_response = USER_EXISTS;
                std::cout << "login" << std::endl;
                peer.send(&c_response, sizeof(char));
            } else if (c_cmd == SIGNUP_COMMAND) {
                char c_response = 0;
                std::cout << "signup" << std::endl;
                peer.send(&c_response, sizeof(char));
            } else if (c_cmd == CREATE_COMMAND){
                char c_response = 1;
                std::cout << "create" << std::endl;
                peer.send(&c_response, sizeof(char));
            }
        }
    } catch (std::exception &e){

    }
}