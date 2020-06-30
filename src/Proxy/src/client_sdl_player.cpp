//
// Created by agustin on 8/6/20.
//

#include "client_sdl_player.h"
#include "common_message.h"
#include "client_sdl_camera.h"
#include "client_sdl_window.h"

#define HUMANOID_HEAD_WIDTH 17
#define HUMANOID_HEAD_HEIGHT 15

SdlPlayer::SdlPlayer(SdlWindow &window, SdlTextureManager &textureManager) :
        bodyTexture( "../../Proxy/assets/340.gif", window),
        headSpriteSheetTexture(32, 32, "../../Proxy/assets/2005.gif", window){
    pos_x = 0;
    pos_y = 0;

    //width = 17;
    //height = 15;

    vel_x = 0;
    vel_y = 0;

    //Cargo el vector con cada sprite de la cabeza
    for (int i = 0; i < TOTAL_HEAD_SPRITE; ++i) {
        head_sprite_clips[i] = {i * HUMANOID_HEAD_WIDTH, 0, HUMANOID_HEAD_WIDTH, HUMANOID_HEAD_HEIGHT};
    }

    e_face_orientation = FRONT_HEAD_SPRITE;
}


void SdlPlayer::handleEvent(SDL_Event &e, bool &is_event_handled) {
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch(e.key.keysym.sym){
            case SDLK_UP: vel_y -= VEL;
            e_face_orientation = BACK_HEAD_SPRITE;
            break;
            case SDLK_DOWN: vel_y += VEL;
            e_face_orientation = FRONT_HEAD_SPRITE;
            break;
            case SDLK_LEFT: vel_x -= VEL;
            e_face_orientation = LEFT_HEAD_SPRITE;
            break;
            case SDLK_RIGHT: vel_x += VEL;
            e_face_orientation = RIGHT_HEAD_SPRITE;
            break;

        }
    }
    /*Cuando se suelta la tecla tenemos que deshacer los cambios*/
    /*if(e.type == SDL_KEYUP && e.key.repeat == 0){
        switch(e.key.keysym.sym){
            case SDLK_UP: vel_y += VEL; break;
            case SDLK_DOWN: vel_y -= VEL; break;
            case SDLK_LEFT: vel_x += VEL; break;
            case SDLK_RIGHT: vel_x -= VEL; break;

        }
    }*/

}


/*Logic*/
/*Crea el msg con el offset al que se quiere mover, lo encola en @param clientEvents*/
void SdlPlayer::move(BlockingQueue<std::unique_ptr<Message>> &clientEvents) {
    //Si se movio
    if(vel_x != 0 || vel_y != 0){
        clientEvents.push(std::unique_ptr<Message> (
                new Movement(vel_x, vel_y)));
        vel_x = 0;
        vel_y = 0;
    }
}

void SdlPlayer::update(const int player_x, const int player_y, SdlCamera &camera) {
    this->pos_x = camera.toPixels(player_x);
    this->pos_y = camera.toPixels(player_y);
}

void SdlPlayer::update(SdlTexture& weapon_sprite, SdlTexture& shield_sprite) {

}

void SdlPlayer::render(SdlCamera &camera) {
    //Muestra la cabeza y el cuerpo del npc
    /*headSpriteSheetTexture.render((pos_x + (bodyTexture.getWidth() - HUMANOID_HEAD_WIDTH) / 2) - camera.getX(),
                                  (pos_y - HUMANOID_HEAD_HEIGHT) - camera.getY(),
                                  &head_sprite_clips[e_face_orientation]);*/
    //bodyTexture.render(pos_x - camera.getX(), pos_y - camera.getY());
    headSpriteSheetTexture.render(pos_x - camera.getX(),
                                  pos_y - camera.getY(),
                                  &head_sprite_clips[e_face_orientation]);
}


int SdlPlayer::getPosX() const {
    return this->pos_x;
}

int SdlPlayer::getPosY() const {
    return this->pos_y;
}
