//
// Created by agustin on 13/6/20.
//

#ifndef ARGENTUM_CLIENT_CLIENT_H
#define ARGENTUM_CLIENT_CLIENT_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
#include "client_sdl_texture.h"
#include "client_sdl_window.h"
#include "client_sdl_player.h"
#include "common_blocking_queue.h"
#include "client_sdl_button.h"
#include "client_command.h"
#include "common_proxy_socket.h"
#include "client_th_send.h"
#include "client_protected_list.h"
#include "client_th_recv.h"
#include "client_sdl_world.h"
#include "client_gui.h"

class Client {
private:
    ProxySocket& proxySocket;
    BlockingQueue<std::unique_ptr<Message>> clientEvents;
    ProtectedList<std::unique_ptr<Message>> serverEvents;
    ThSend thSend;
    ThRecv thRecv;
    GUI gui;

public:
    //Start up SDL and create window
    explicit Client(ProxySocket& proxySocket);

    int run();

    void init();

    void update();

    void stop();

    /*Cierra SDL y libera los recursos*/
    ~Client();

};


#endif //ARGENTUM_CLIENT_CLIENT_H
