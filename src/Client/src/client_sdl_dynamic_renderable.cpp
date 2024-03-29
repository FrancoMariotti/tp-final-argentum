//
// Created by agustin on 24/6/20.
//

#include "client_sdl_dynamic_renderable.h"
#include "client_sdl_camera.h"
#include "client_sdl_texture.h"
#include "Common/OsException.h"

SdlDynamicRenderable::SdlDynamicRenderable(int x, int y, SdlTextureManager &textureManager, const SdlWindow &window,
                                           TTF_Font *font, const std::string s_tag, const SDL_Color color,
                                           SdlAudioManager &audioManager) :
        pos_x(x),
        pos_y(y),
        old_x(x),
        old_y(y),
        of_x(0), of_y(0),
        animation_frame(0),
        is_moving(false),
        textureManager(textureManager),
        audioManager(audioManager),
        body_or(SdlTextureManager::FRONT),
        head_or(SdlTextureManager::FRONT_HEAD_SPRITE),
        tag(pos_x, pos_y, "<" + s_tag + ">", font, window, color),
        healthBar(pos_x, pos_y, 40, 2, 0xFF, 0, 0, 0xFF, window)
        {}

void SdlDynamicRenderable::updatePos(int new_x, int new_y, SdlCamera &camera) {
    this->old_x = pos_x;
    this->old_y = pos_y;
    pos_x = camera.toPixels(new_x);
    pos_y = camera.toPixels(new_y);
    this->of_x = pos_x - old_x;
    this->of_y = pos_y - old_y;
    if(pos_x > old_x && abs(of_x) > abs(of_y)){
        head_or = SdlTextureManager::RIGHT_HEAD_SPRITE;
        body_or = SdlTextureManager::RIGHT;
    } else if(pos_x < old_x && abs(of_x) > abs(of_y)){
        head_or = SdlTextureManager::LEFT_HEAD_SPRITE;
        body_or = SdlTextureManager::LEFT;
    } else if(pos_y > old_y && abs(of_x) <= abs(of_y)){
        head_or = SdlTextureManager::FRONT_HEAD_SPRITE;
        body_or = SdlTextureManager::FRONT;
    } else if(pos_y < old_y && abs(of_x) <= abs(of_y)){
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
        if (animation_frame >= SdlTextureManager::MAX_FRAMES) {
            is_moving = false;
        } else {
            animation_frame++;
        }
    }
}

/*Elimina los efectos que ya terminaron y agrega el nuevo efecto a la lista*/
void SdlDynamicRenderable::addVisualEffect(const std::string& effect_id) {
    std::vector<SdlEffect>::iterator it = effects.begin();
    while (it != effects.end()) {
        if (it->isFinish()) {
            it = effects.erase(it);
        } else {
            it++;
        }
    }
    effects.emplace_back(textureManager.getEffectSpriteTexture(effect_id),
                         effect_id,
                         audioManager);
}

void SdlDynamicRenderable::renderEffects(const SdlCamera& camera){
    /*Reproduce todos los efectos pendientes de la lista de efectos*/
    for(auto it = effects.begin(); it != effects.end(); it++){
        it->render(pos_x + camera.getTileSize()/2 - camera.getX(), pos_y - camera.getTileSize()/2 - camera.getY());
    }
}

int SdlDynamicRenderable::getPosX() const {
    return pos_x;
}

int SdlDynamicRenderable::getPosY() const {
    return pos_y;
}

SDL_Point SdlDynamicRenderable::getPos() const {
    return SDL_Point{pos_x, pos_y};
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
        pos_x = old_x + ((of_x / SdlTextureManager::MAX_FRAMES) * animation_frame);
        pos_y = old_y + ((of_y / SdlTextureManager::MAX_FRAMES) * animation_frame);
        textureManager.renderMovingNPC(texture_id, old_x, old_y,
                body_or, of_x, of_y, animation_frame, camera);
    } else {
        textureManager.renderStillNPC(texture_id, pos_x,
                                      pos_y, body_or, camera);
        tag.render(pos_x - camera.getX(),pos_y - camera.getY());
        healthBar.render(pos_x - camera.getX(), pos_y - camera.getY());
    }
    SdlDynamicRenderable::renderEffects(camera);
    this->endAnimationIfComplete();
}

void SdlRenderableNPC::updateEquipment(const equipment_t &equipment) {
    throw OSError{"SdlRenderableNPC:updateEquipment, NPC doesnt have equipment"};
}

SdlRenderablePlayable::SdlRenderablePlayable(int x, int y, SdlTextureManager &textureManager,
                                             const std::string& username, const std::string& race,
                                             const equipment_t& equipment, TTF_Font *font, const SdlWindow &window,
                                             SdlAudioManager &audioManager) :
        SdlDynamicRenderable(x, y, textureManager, window, font,
                             username, SDL_Color{0, 0, 0xFF, 0xFF}, audioManager),
        username(username),
        RACE(race),
        t_appearance{race + "Head",equipment.helmetName,equipment.armourName,
                     equipment.weaponName,equipment.shieldName}
        {}

void SdlRenderablePlayable::updateEquipment(const equipment_t &equipment) {
    t_appearance.weapon = equipment.weaponName;
    t_appearance.armour = equipment.armourName;
    t_appearance.helmet = equipment.helmetName;
    t_appearance.shield = equipment.shieldName;
}

void SdlRenderablePlayable::render(const SdlCamera &camera) {
    if(is_moving){
        pos_x = old_x + ((of_x / SdlTextureManager::MAX_FRAMES) * animation_frame);
        pos_y = old_y + ((of_y / SdlTextureManager::MAX_FRAMES) * animation_frame);
        textureManager.renderMovingPC(t_appearance, of_x, of_y,
                                       camera, old_x, old_y,
                                       animation_frame,
                                       body_or, head_or);
    } else{
        textureManager.renderStillPC(t_appearance, pos_x, pos_y,
                                     camera, body_or, head_or);
        tag.render(pos_x - camera.getX(),pos_y - camera.getY());
    }
    SdlDynamicRenderable::renderEffects(camera);

    this->endAnimationIfComplete();
}

