//
// Created by agustin on 12/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_BUTTON_H
#define ARGENTUM_CLIENT_SDL_BUTTON_H

#include <SDL2/SDL_events.h>
#include "client_sdl_texture.h"
#include "common_blocking_queue.h"
#include "client_command.h"
#include "common_proxy_socket.h"
#include "client_sdl_camera.h"
#include "client_sdl_mouse.h"

class Message;
class SdlButton {
private:
    enum e_outline_sprite{
        OUTLINE_SPRITE_MOUSE_OVER_MOTION,
        OUTLINE_SPRITE_MOUSE_OUT,
        OUTLINE_SPRITE_TOTAL,
    };

    int width;
    int height;
    int left_click;
    int right_click;

    SDL_Point position;
    //Currently used sprite
    e_outline_sprite outline_sprite;
    //Sprites de cada estado del boton
    SDL_Rect outline_sprite_clips[OUTLINE_SPRITE_TOTAL];
    //Imagen del boton
    SdlTexture& buttonSpriteSheetTexture;
    SdlTexture& outlineTexture;

    /**TODO: para indicar cantidad de items (e.g. pociones) o si esta equipado (E)*/
    /*SdlOutput buttonText*/

    Use cmd;

public:
    SdlButton(SdlTexture& buttonTexture, SdlTexture& outlineTexture);
    void setPosition(int x, int y);
    //Handles mouse event
    void handleEvent(SDL_Event &e, bool &is_event_handled);
    /*Si el jugador hizo click en algun item envia el comando a la cola de eventos*/
    void use(BlockingQueue<std::unique_ptr<Message>> &clientEvents, int i, SdlMouse &mouse);
    /*Muestra los sprites de los botones*/
    void render();
    ~SdlButton() = default;

};


#endif //ARGENTUM_CLIENT_SDL_BUTTON_H
