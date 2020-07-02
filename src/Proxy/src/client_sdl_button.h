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
        enum e_button_sprite{
            BUTTON_SPRITE_MOUSE_OUT = 0,
            BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
            BUTTON_SPRITE_MOUSE_DOWN = 2,
            BUTTON_SPRITE_MOUSE_UP = 3,
            BUTTON_SPRITE_TOTAL = 4,
        };

        int width;
        int height;
        int double_click;
        int single_click;

        SDL_Point position;
        //Currently used sprite
        e_button_sprite current_sprite;
        e_button_sprite outline_sprite;
        //Sprites de cada estado del boton
        SDL_Rect button_sprite_clips[BUTTON_SPRITE_TOTAL];
        SDL_Rect outline_sprite_clips[BUTTON_SPRITE_TOTAL];
        //Imagen del boton
        SdlTexture& buttonSpriteSheetTexture;
        SdlTexture& outlineTexture;

        /**TODO: para indicar cantidad de items (e.g. pociones) o si esta equipado (E)*/
        /*SdlOutput buttonText*/

        Use cmd;

    public:
        //Initialize internal variables
        SdlButton(SdlTexture& buttonTexture, SdlTexture& outlineTexture);

        //Sets top left position
        void setPosition(int x, int y);

        //Handles mouse event
        void handleEvent(SDL_Event &e, bool &is_event_handled);

        void use(BlockingQueue<std::unique_ptr<Message>> &clientEvents, int i, SdlMouse &mouse);

        //Shows button sprite
        void render();

        ~SdlButton();

};


#endif //ARGENTUM_CLIENT_SDL_BUTTON_H
