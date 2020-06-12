//
// Created by agustin on 12/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_BUTTON_H
#define ARGENTUM_CLIENT_SDL_BUTTON_H

#include <SDL2/SDL_events.h>
#include "client_sdl_texture.h"

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
    //Top left position
    SDL_Point position;
    //Currently used sprite
    e_button_sprite current_sprite;
    //Sprites de cada estado del boton
    SDL_Rect button_sprite_clips[BUTTON_SPRITE_TOTAL];

    SdlTexture& buttonSpriteSheetTexture;

    public:
        //Initialize internal variables
        SdlButton(int width, int height, SdlTexture& button);

        //Sets top left position
        /**Los items se van a ir moviendo en el inventario asi que necesito un set*/
        void setPosition(int x, int y);

        //Handles mouse event
        void handleEvent(SDL_Event* e);

        //Shows button sprite
        void render();

};


#endif //ARGENTUM_CLIENT_SDL_BUTTON_H
