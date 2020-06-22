//
// Created by agustin on 8/6/20.
//

#include <iostream>
#include "client_sdl_player.h"
#include "client_sdl_texture.h"
#include "common_message.h"

#define HUMANOID_HEAD_WIDTH 17
#define HUMANOID_HEAD_HEIGHT 15

SdlPlayer::SdlPlayer(int x, int y, SdlTexture &texture, SdlTexture &head) :
        bodyTexture(texture),
        headSpriteSheetTexture(head){
    //Initialize the offsets
    pos_x = x;
    pos_y = y;

    width = texture.getWidth();
    height = texture.getHeight();

    //Initialize the velocity
    vel_x = 0;
    vel_y = 0;

    //Cargo el vector con cada sprite de la cabeza
    for (int i = 0; i < TOTAL_HEAD_SPRITE; ++i) {
        head_sprite_clips[i] = {i * HUMANOID_HEAD_WIDTH, 0, HUMANOID_HEAD_WIDTH, HUMANOID_HEAD_HEIGHT};
    }

    e_face_orientation = FRONT_HEAD_SPRITE;
}


void SdlPlayer::handleEvent(SDL_Event &e) {
    //if a key was pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        //Adjust the velocity
        switch(e.key.keysym.sym){
            case SDLK_UP: vel_y -= VEL; break;
            case SDLK_DOWN: vel_y += VEL; break;
            case SDLK_LEFT: vel_x -= VEL; break;
            case SDLK_RIGHT: vel_x += VEL; break;

        }
    }
    //if key was released
    /*Cuando se suelta la tecla tenemos que deshacer los cambios*/
    if(e.type == SDL_KEYUP && e.key.repeat == 0){
        switch(e.key.keysym.sym){
            case SDLK_UP: vel_y += VEL; break;
            case SDLK_DOWN: vel_y -= VEL; break;
            case SDLK_LEFT: vel_x += VEL; break;
            case SDLK_RIGHT: vel_x -= VEL; break;

        }
    }
}


void SdlPlayer::render() {
    //Muestra la cabeza y el cuerpo del npc
    headSpriteSheetTexture.render(pos_x + (bodyTexture.getWidth() - HUMANOID_HEAD_WIDTH) / 2,
                                       pos_y - HUMANOID_HEAD_HEIGHT,
                                  &head_sprite_clips[e_face_orientation]);
    bodyTexture.render(pos_x, pos_y);
}

/*Logic*/
/*Crea el msg con el offset al que se quiere mover, lo encola en @param clientEvents*/
void SdlPlayer::move(BlockingQueue<std::unique_ptr<Message>> &clientEvents) {
    //Si se movio
    if(vel_x != 0 || vel_y != 0){
        clientEvents.push(std::unique_ptr<Message> (
                new Movement(vel_x, vel_y)));
        //CODIGO DE PRUEBA
        //pos_x += vel_x;
        //pos_y += vel_y;
        //FIN CODIGO DE PRUEBA
    }
}
