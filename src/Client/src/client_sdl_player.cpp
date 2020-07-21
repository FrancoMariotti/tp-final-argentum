//
// Created by agustin on 8/6/20.
//

#include "client_sdl_player.h"
#include "Common/Messages/Message.h"
#include "client_sdl_camera.h"
#include "client_sdl_window.h"

SdlPlayer::SdlPlayer(SdlTextureManager &textureManager) :
        textureManager(textureManager),
        is_moving(false),
        body_or(SdlTextureManager::FRONT),
        head_or(SdlTextureManager::FRONT_HEAD_SPRITE),
        t_appearance{"humanHead","none","defaultArmour","none","none"}{
    pos_x = 0;
    pos_y = 0;
    old_x = 0;
    old_y = 0;
    animation_frame = 0;
}

void SdlPlayer::updatePos(const int player_x, const int player_y, SdlCamera &camera) {
    this->old_x = pos_x;
    this->old_y = pos_y;
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
    this->startAnimation();
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

void SdlPlayer::render(SdlCamera &camera, SdlTimer &timer) {
    if(is_moving){
        int of_x = pos_x - old_x;
        int of_y = pos_y - old_y;
        textureManager.renderMovingPC(t_appearance, of_x, of_y,
                                      camera, old_x, old_y,
                                      animation_frame,
                                      body_or, head_or);
    } else {
        textureManager.renderStillPC(t_appearance, pos_x, pos_y,
                camera, body_or, head_or);
    }
    this->endAnimationIfComplete();
}


void SdlPlayer::startAnimation() {
    animation_frame = 0;
    is_moving = true;
}

void SdlPlayer::endAnimationIfComplete() {
    if(is_moving) {
        if (animation_frame >= MAX_FRAMES) {
            is_moving = false;
        } else {
            animation_frame++;
        }
    }
}

int SdlPlayer::getPosX() const {
    return this->pos_x;
}

int SdlPlayer::getPosY() const {
    return this->pos_y;
}
