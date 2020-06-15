//
// Created by agustin on 12/6/20.
//

#include <iostream>
#include "client_sdl_button.h"
#include "common_proxy_socket.h"

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 200

/**TODO: Hacer un overload para el caso de que no
 * tengan spritesheet y sean imagenes estaticas*/

SdlButton::SdlButton(SdlTexture& buttonTexture, Command* cmd) :
    buttonSpriteSheetTexture(buttonTexture),
    cmd(cmd){
    position.x = 0;
    position.y = 0;

    this->width = buttonTexture.getWidth();
    this->height = buttonTexture.getHeight();

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

        /*Boton no se clickeo*/
        this->clicked = false;

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
            //Set mouseover sprite
            switch (e->type){
                case SDL_MOUSEMOTION:
                    current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                    if(e->button.button == SDL_BUTTON_LEFT){
                        this->clicked = true;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    current_sprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }

}

void SdlButton::use(ProxySocket &proxySocket, int i) {
    if(clicked){
        (*cmd)(proxySocket, i);
        /*Test*/
        t_command msg = proxySocket.readServer();
        std::cout << msg.command << "item pos: " << msg.x << std::endl;
    }
}

void SdlButton::render() {
    //Show current button sprite
    this->buttonSpriteSheetTexture.render(position.x, position.y, &this->button_sprite_clips[current_sprite]);
}

SdlButton::~SdlButton() {
    delete cmd;
}
