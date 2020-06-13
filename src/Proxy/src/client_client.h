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

//Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480



class Client {
private:
    //Start up SDL and create window
    SdlWindow window;
    SdlTexture background;
    ProxySocket proxySocket;

public:
    Client();
    int run();

private:
    void close();
};


#endif //ARGENTUM_CLIENT_CLIENT_H
