//
// Created by agustin on 24/6/20.
//

#include "client_sdl_dynamic_renderable.h"
#include "client_sdl_camera.h"
#include "client_sdl_texture.h"

SdlDynamicRenderable::SdlDynamicRenderable(const int x, const int y,
        SdlTextureManager &textureManager, const std::string texture_id) :
        pos_x(x),
        pos_y(y),
        texture_id(texture_id),
        textureManager(textureManager),
        body_or(SdlTextureManager::FRONT)
        {}

void SdlDynamicRenderable::update(const int new_x, const int new_y, SdlCamera &camera) {
    int old_x = pos_x;
    int old_y = pos_y;
    pos_x = camera.toPixels(new_x);
    pos_y = camera.toPixels(new_y);
    if(pos_x > old_x){
        body_or = SdlTextureManager::RIGHT;
    } else if(pos_x < old_x){
        body_or = SdlTextureManager::LEFT;
    } else if(pos_y > old_y){
        body_or = SdlTextureManager::FRONT;
    } else if(pos_y < old_y){
        body_or = SdlTextureManager::BACK;
    }
}

void SdlDynamicRenderable::render(const SdlCamera& camera){
    textureManager.renderNPC(texture_id, pos_x - camera.getX(),
            pos_y - camera.getY(), body_or);
}
