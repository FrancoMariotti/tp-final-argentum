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
        textureManager(textureManager),
        body_or(SdlTextureManager::FRONT),
        head_or(SdlTextureManager::FRONT_HEAD_SPRITE)
        {}

void DynamicRenderable::updatePos(int new_x, int new_y, SdlCamera &camera) {
    int old_x = pos_x;
    int old_y = pos_y;
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
}

RenderableNPC::RenderableNPC(const int x, const int y,
        SdlTextureManager &textureManager, const std::string texture_id) :
        DynamicRenderable(x,y,textureManager),
        texture_id(texture_id)
        {}

void RenderableNPC::render(const SdlCamera& camera){
    textureManager.renderNPC(texture_id, pos_x - camera.getX(),
            pos_y - camera.getY(), body_or);
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
    textureManager.renderPC(t_appearance, pos_x, pos_y,
                            camera, body_or, head_or);
}

