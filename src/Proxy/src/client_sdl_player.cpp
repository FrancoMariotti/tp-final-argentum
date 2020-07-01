//
// Created by agustin on 8/6/20.
//

#include "client_sdl_player.h"
#include "common_message.h"
#include "client_sdl_camera.h"
#include "client_sdl_window.h"

SdlPlayer::SdlPlayer(SdlTextureManager &textureManager) :
        textureManager(textureManager),
        body_or(SdlTextureManager::FRONT),
        head_or(SdlTextureManager::FRONT_HEAD_SPRITE),
        t_appearance{"humanHead","defaultArmour","none","none","none"}{
    pos_x = 0;
    pos_y = 0;
}

void SdlPlayer::updatePos(const int player_x, const int player_y, SdlCamera &camera) {
    int old_x = pos_x;
    int old_y = pos_y;
    this->pos_x = camera.toPixels(player_x);
    this->pos_y = camera.toPixels(player_y);
    if(pos_x > old_x){
        head_or = SdlTextureManager::RIGHT_HEAD_SPRITE;
        body_or = SdlTextureManager::RIGHT;
    } else if(pos_x < old_x){
        head_or = SdlTextureManager::LEFT_HEAD_SPRITE;
        body_or = SdlTextureManager::LEFT;
    } else if(pos_y > old_y){
        head_or = SdlTextureManager::FRONT_HEAD_SPRITE;
        body_or = SdlTextureManager::FRONT;
    } else if(pos_y < old_y){
        head_or = SdlTextureManager::BACK_HEAD_SPRITE;
        body_or = SdlTextureManager::BACK;
    }
}

void SdlPlayer::updateEquipment(const equipment_t& equipment) {
    /*rompe pq no tengo "fists" en el map de texturas*/
    //std::cout << equipment.weaponName << std::endl;

    if(equipment.weaponName != "fists"){

    }
}

void SdlPlayer::render(SdlCamera &camera) {
    SdlTextureManager::t_player_appearance appearance{"humanHead","ironHelmet",
                                           "defaultArmour","axe","ironShield"};
    textureManager.renderPC(appearance, pos_x, pos_y, camera, body_or, head_or);

    /*
    int body_offset_y = armourSpriteSheetTexture->getHeight() - 32;

    headSpriteSheetTexture->render((pos_x + (armourSpriteSheetTexture->getWidth() - headSpriteSheetTexture->getWidth() )/ 2) - camera.getX(),
                                  (pos_y - headSpriteSheetTexture->getHeight() - body_offset_y) - camera.getY(),
                                  &head_orientation_clips[e_face_orientation]);
    armourSpriteSheetTexture->render(pos_x - camera.getX(),
            (pos_y - body_offset_y) - camera.getY(),
            &armour_orientation_clips[e_body_orientation]);
    weaponSpriteSheetTexture->render(pos_x - camera.getX(),
            (pos_y - body_offset_y) - camera.getY(),
            &weapon_orientation_clips[e_body_orientation]);
    shieldSpriteSheetTexture->render(pos_x - camera.getX(),
            (pos_y - body_offset_y) - camera.getY(),
            &shield_orientation_clips[e_body_orientation]);
*/
}


int SdlPlayer::getPosX() const {
    return this->pos_x;
}

int SdlPlayer::getPosY() const {
    return this->pos_y;
}
