//
// Created by agustin on 12/6/20.
//

#include "client_sdl_button.h"

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 200

SdlButton::SdlButton(int width, int height, SdlTexture& button) :
    buttonSpriteSheetTexture(button){

    position.x = 0;
    position.y = 0;

    this->width = width;
    this->height = height;

    //Cargo el vector con cada sprite de la cabeza
    for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
        this->button_sprite_clips[i] = {0, i * BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT};
    }

    this->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
}

void SdlButton::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void SdlButton::handleEvent(SDL_Event *e) {
    //if mouse even happend
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP){
        int x,y;
        /*Devuelve la posicion del mouse*/
        SDL_GetMouseState(&x,&y);

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if(x < position.x){
            inside = false;
        } else if (x > position.x + width ){
            inside = false;
        } else if (y < position.y){
            inside = false;
        } else if (y > position.y + height){
            inside = false;
        }
        if (!inside){
            current_sprite = BUTTON_SPRITE_MOUSE_OUT;
        }
            //Mouse is inside button
        else {
            //Set mouse over sprite
            switch (e->type){
                case SDL_MOUSEMOTION:
                    current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                case SDL_MOUSEBUTTONUP:
                    current_sprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }

}

void SdlButton::render() {
    //Show current button sprite
    this->buttonSpriteSheetTexture.render(position.x, position.y, &this->button_sprite_clips[current_sprite]);
}
