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
#include "Common/BlockingQueue.h"
#include "client_sdl_button.h"
#include "client_command.h"
#include "Common/common_proxy_socket.h"
#include "client_th_send.h"
#include "client_protected_list.h"
#include "client_th_recv.h"
#include "client_sdl_world.h"
#include "client_gui.h"
#include "Common/Socket.h"

class Client {
private:
    //SdlWindow window;
    //SdlTexture mainInterface;
    //TTF_Font* font;
    Socket& socket;
    BlockingQueue<std::unique_ptr<Message>> clientEvents;
    ProtectedList<std::unique_ptr<Message>> serverEvents;
    ThSend thSend;
    ThRecv thRecv;
    GUI gui;

public:
    //Start up SDL and create window
    Client(const std::string &hostname, const std::string &service, Socket &socket);

    //explicit Client(ProxySocket& proxySocket);

    int run();

    void init();

    void update();

    void stop();

    /*Cierra SDL y libera los recursos*/
    ~Client();

};


#endif //ARGENTUM_CLIENT_CLIENT_H
