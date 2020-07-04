//
// Created by agustin on 24/6/20.
//

#include "client_sdl_dynamic_renderable.h"
#include "client_sdl_camera.h"
#include "client_sdl_texture.h"
#include "common_osexception.h"

DynamicRenderable::DynamicRenderable(int x, int y, SdlTextureManager &textureManager) :
        pos_x(x),
        pos_y(y),
        old_x(0),
        old_y(0),
        animation_frame(0),
        is_moving(false),
        textureManager(textureManager),
        body_or(SdlTextureManager::FRONT),
        head_or(SdlTextureManager::FRONT_HEAD_SPRITE)
        {}

void DynamicRenderable::updatePos(int new_x, int new_y, SdlCamera &camera) {
    this->old_x = pos_x;
    this->old_y = pos_y;
    pos_x = camera.toPixels(new_x);
    pos_y = camera.toPixels(new_y);
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

void DynamicRenderable::startAnimation() {
    animation_frame = 0;
    is_moving = true;
}

void DynamicRenderable::endAnimationIfComplete() {
    if(is_moving) {
        if (animation_frame >= MAX_FRAMES) {
            is_moving = false;
        } else {
            animation_frame++;
        }
    }
}


RenderableNPC::RenderableNPC(const int x, const int y,
        SdlTextureManager &textureManager, const std::string texture_id) :
        DynamicRenderable(x,y,textureManager),
        texture_id(texture_id)
        {}

void RenderableNPC::render(const SdlCamera& camera){
    if(is_moving){
        int of_x = pos_x - old_x;
        int of_y = pos_y - old_y;
        textureManager.renderMovingNPC(texture_id, old_x, old_y,
                body_or, of_x, of_y, animation_frame, camera);
    } else{
        textureManager.renderStillNPC(texture_id, pos_x,
                                      pos_y, body_or, camera);
    }
    this->endAnimationIfComplete();
}

void RenderableNPC::updateEquipment(const equipment_t &equipment) {
    throw OSError{"RenderableNPC:updateEquipment, NPC doesnt have equipment"};
}

RenderablePlayable::RenderablePlayable(int x, int y, SdlTextureManager &textureManager) :
        DynamicRenderable(x,y,textureManager),
        t_appearance{"humanHead","none","defaultArmour",
                     "none","none"}
        {}

void RenderablePlayable::updateEquipment(const equipment_t &equipment) {
    t_appearance.weapon = equipment.weaponName;
    t_appearance.armour = equipment.armourName;
    t_appearance.helmet = equipment.helmetName;
    t_appearance.shield = equipment.shieldName;
}

void RenderablePlayable::render(const SdlCamera &camera) {
    textureManager.renderStillPC(t_appearance, pos_x, pos_y,
                            camera, body_or, head_or);
}

