//
// Created by agustin on 8/6/20.
//

#include "client_sdl_player.h"
#include "common_message.h"
#include "client_sdl_camera.h"
#include "client_sdl_window.h"

SdlPlayer::SdlPlayer(SdlWindow &window, SdlTextureManager &textureManager) :
        armourSpriteSheetTexture(textureManager.initArmour()),
        headSpriteSheetTexture(textureManager.initHead()),
        weaponSpriteSheetTexture(textureManager.initWeapon()),
        shieldSpriteSheetTexture(textureManager.initShield()),
        e_body_orientation(FRONT){
    pos_x = 0;
    pos_y = 0;
    //width = 17;
    //height = 15;

    vel_x = 0;
    vel_y = 0;

    for (int i = 0; i < TOTAL_HEAD_SPRITE ; ++i) {
        head_orientation_clips[i] = {i*headSpriteSheetTexture.getWidth(), 0, headSpriteSheetTexture.getWidth(), headSpriteSheetTexture.getHeight()};
    }
    for (int i = 0; i < TOTAL_ORIENTATIONS ; ++i) {
        armour_orientation_clips[i] = {0, i*armourSpriteSheetTexture.getHeight(), armourSpriteSheetTexture.getWidth(), armourSpriteSheetTexture.getHeight()};
        weapon_orientation_clips[i] = {0, i*weaponSpriteSheetTexture.getHeight(), weaponSpriteSheetTexture.getWidth(), weaponSpriteSheetTexture.getHeight()};
        shield_orientation_clips[i] = {0, i*shieldSpriteSheetTexture.getHeight(), shieldSpriteSheetTexture.getWidth(), shieldSpriteSheetTexture.getHeight()};
    }

    e_face_orientation = FRONT_HEAD_SPRITE;
}

void SdlPlayer::handleEvent(SDL_Event &e, bool &is_event_handled) {
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch(e.key.keysym.sym){
            case SDLK_UP: vel_y -= VEL;
            e_body_orientation = BACK;
            e_face_orientation = BACK_HEAD_SPRITE;
            break;
            case SDLK_DOWN: vel_y += VEL;
            e_body_orientation = FRONT;
            e_face_orientation = FRONT_HEAD_SPRITE;
            break;
            case SDLK_LEFT: vel_x -= VEL;
            e_body_orientation = LEFT;
            e_face_orientation = LEFT_HEAD_SPRITE;
            break;
            case SDLK_RIGHT: vel_x += VEL;
            e_body_orientation = RIGHT;
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
    /*headSpriteSheetTexture.render((pos_x + (armourSpriteSheetTexture.getWidth() - HUMANOID_HEAD_WIDTH) / 2) - camera.getX(),
                                  (pos_y - HUMANOID_HEAD_HEIGHT) - camera.getY(),
                                  &head_sprite_clips[e_face_orientation]);*/

    int body_offset_y = armourSpriteSheetTexture.getHeight() - 32;

    headSpriteSheetTexture.render((pos_x + (armourSpriteSheetTexture.getWidth() - headSpriteSheetTexture.getWidth() )/ 2) - camera.getX(),
                                  (pos_y - headSpriteSheetTexture.getHeight() - body_offset_y) - camera.getY(),
                                  &head_orientation_clips[e_face_orientation]);
    armourSpriteSheetTexture.render(pos_x - camera.getX(),
            (pos_y - body_offset_y) - camera.getY(),
            &armour_orientation_clips[e_body_orientation]);
    //weaponSpriteSheetTexture.render(pos_x - camera.getX(),
    // (pos_y - body_offset_y) - camera.getY(),
    // &weapon_orientation_clips[e_body_orientation]);
    //shieldSpriteSheetTexture.render(pos_x - camera.getX(),
    // (pos_y - body_offset_y) - camera.getY(),
    // &shield_orientation_clips[e_body_orientation]);

}


int SdlPlayer::getPosX() const {
    return this->pos_x;
}

int SdlPlayer::getPosY() const {
    return this->pos_y;
}
