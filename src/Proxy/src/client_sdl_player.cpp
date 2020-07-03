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
        t_appearance{"humanHead","none","defaultArmour","none","none"}{
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
    std::cout << "DEBUG: " << equipment.weaponName << std::endl;
    std::cout << "DEBUG: " << equipment.armourName << std::endl;
    std::cout << "DEBUG: " << equipment.shieldName << std::endl;
    std::cout << "DEBUG: " << equipment.helmetName << std::endl;
    t_appearance.weapon = equipment.weaponName;
    t_appearance.armour = equipment.armourName;
    t_appearance.helmet = equipment.helmetName;
    t_appearance.shield = equipment.shieldName;
}

void SdlPlayer::render(SdlCamera &camera) {
    textureManager.renderPC(t_appearance, pos_x, pos_y,
            camera, body_or, head_or);

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
