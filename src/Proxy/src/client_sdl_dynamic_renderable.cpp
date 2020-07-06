//
// Created by agustin on 24/6/20.
//

#include "client_sdl_dynamic_renderable.h"
#include "client_sdl_camera.h"
#include "client_sdl_texture.h"
#include "common_osexception.h"

SdlDynamicRenderable::SdlDynamicRenderable(int x, int y, SdlTextureManager &textureManager, const SdlWindow &window,
                                           TTF_Font *font, const std::string s_tag, const SDL_Color color,
                                           SdlAudioManager &audioManager) :
        pos_x(x),
        pos_y(y),
        old_x(0),
        old_y(0),
        animation_frame(0),
        is_moving(false),
        textureManager(textureManager),
        audioManager(audioManager),
        body_or(SdlTextureManager::FRONT),
        head_or(SdlTextureManager::FRONT_HEAD_SPRITE),
        tag(pos_x, pos_y, "<" + s_tag + ">", font, window, color),
        healthBar(pos_x, pos_y, 40, 2, 0xFF, 0, 0, 0xFF, window),
        effect(textureManager.getEffectSpriteTexture("explosion"), 5, 10)
        {}

void SdlDynamicRenderable::updatePos(int new_x, int new_y, SdlCamera &camera) {
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

void SdlDynamicRenderable::startAnimation() {
    animation_frame = 0;
    is_moving = true;
}

void SdlDynamicRenderable::endAnimationIfComplete() {
    if(is_moving) {
        if (animation_frame >= MAX_FRAMES) {
            is_moving = false;
        } else {
            animation_frame++;
        }
    }
}

void SdlDynamicRenderable::updateStats() {
    effect.setEffect(&textureManager.getEffectSpriteTexture("missile"),1,9);
    audioManager.playSound("explosion", 0);
}


SdlRenderableNPC::SdlRenderableNPC(const int x, const int y, SdlTextureManager &textureManager,
                                   const std::string texture_id, TTF_Font *font, const SdlWindow &window,
                                   SdlAudioManager &audioManager) :
        SdlDynamicRenderable(x, y, textureManager, window, font, texture_id,
                             SDL_Color{0xFF, 0, 0, 0xFF}, audioManager),
        texture_id(texture_id)
        {}

void SdlRenderableNPC::render(const SdlCamera& camera){
    if(is_moving){
        int of_x = pos_x - old_x;
        int of_y = pos_y - old_y;
        textureManager.renderMovingNPC(texture_id, old_x, old_y,
                body_or, of_x, of_y, animation_frame, camera);
    } else {
        textureManager.renderStillNPC(texture_id, pos_x,
                                      pos_y, body_or, camera);
        tag.render(pos_x - camera.getX(),pos_y - camera.getY());
        healthBar.render(pos_x - camera.getX(), pos_y - camera.getY());
    }
    this->endAnimationIfComplete();
}

void SdlRenderableNPC::updateEquipment(const equipment_t &equipment) {
    throw OSError{"SdlRenderableNPC:updateEquipment, NPC doesnt have equipment"};
}

SdlRenderablePlayable::SdlRenderablePlayable(int x, int y, SdlTextureManager &textureManager,
                                             const std::string username, TTF_Font *font, const SdlWindow &window,
                                             SdlAudioManager &audioManager) :
        SdlDynamicRenderable(x, y, textureManager, window, font,
                             username, SDL_Color{0, 0, 0xFF, 0xFF}, audioManager),
        username(username),
        t_appearance{"humanHead","none","defaultArmour",
                     "none","none"}
        {}

void SdlRenderablePlayable::updateEquipment(const equipment_t &equipment) {
    t_appearance.weapon = equipment.weaponName;
    t_appearance.armour = equipment.armourName;
    t_appearance.helmet = equipment.helmetName;
    t_appearance.shield = equipment.shieldName;
}

void SdlRenderablePlayable::render(const SdlCamera &camera) {
    if(is_moving){
        int of_x = pos_x - old_x;
        int of_y = pos_y - old_y;
        textureManager.renderMovingPC(t_appearance, of_x, of_y,
                                       camera, old_x, old_y,
                                       animation_frame,
                                       body_or, head_or);
    } else{
        textureManager.renderStillPC(t_appearance, pos_x, pos_y,
                                     camera, body_or, head_or);
        tag.render(pos_x - camera.getX(),pos_y - camera.getY());
    }
    /*El efecto a cargar deberia ir en una funcion aparte y aca se reporduce*/
    effect.render(pos_x - camera.getX(), pos_y - camera.getY());
    /*fin test*/
    this->endAnimationIfComplete();
}

int SdlRenderablePlayable::getPosX() const {
    return pos_x;
}

int SdlRenderablePlayable::getPosY() const {
    return pos_y;
}
