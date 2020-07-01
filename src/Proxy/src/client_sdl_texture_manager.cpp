//
// Created by agustin on 30/6/20.
//

#include "client_sdl_texture_manager.h"
#include "client_sdl_texture.h"
#include "client_sdl_player.h"


SdlTextureManager::SdlTextureManager(const SdlWindow &window) {
    this->dynamic_renderables_textures.emplace(std::make_pair("spider",
            SdlTexture(54, 34, "../../Proxy/assets/spiderSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("skeleton",
            SdlTexture(26, 54, "../../Proxy/assets/skeletonSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("zombie",
            SdlTexture(24, 46, "../../Proxy/assets/zombieSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("goblin",
            SdlTexture(24, 36, "../../Proxy/assets/goblinSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("noneSprite",
                      SdlTexture(1, 1, "../../Proxy/items/noneSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("swordSprite",
            SdlTexture(22, 48, "../../Proxy/items/swordSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("axeSprite",
            SdlTexture(22, 48, "../../Proxy/items/axeSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("defaultArmourSprite",
            SdlTexture(24, 46, "../../Proxy/items/defaultArmourSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("ironArmourSprite",
            SdlTexture(24, 46, "../../Proxy/items/ironArmourSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("humanHeadSprite",
            SdlTexture(HEAD_WIDTH, HEAD_HEIGHT, "../../Proxy/assets/humanHeadSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("ironHelmetSprite",
            SdlTexture(HEAD_WIDTH, HEAD_HEIGHT, "../../Proxy/items/ironHelmetSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("turtleShellSprite",
            SdlTexture(25, 44, ITEMS_PATH + "turtleShellSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("ironShieldSprite",
            SdlTexture(25, 44, "../../Proxy/items/ironShieldSprite.png", window)));
}

SdlTexture& SdlTextureManager::initHead(){
    return dynamic_renderables_textures.at("humanHeadSprite");
}

SdlTexture& SdlTextureManager::initArmour(){
    return dynamic_renderables_textures.at("defaultArmourSprite");
}

SdlTexture& SdlTextureManager::initShield(){
    return dynamic_renderables_textures.at("ironShieldSprite");
}

SdlTexture& SdlTextureManager::initWeapon(){
    return dynamic_renderables_textures.at("axeSprite");
}

SdlTexture &SdlTextureManager::initHelmet() {
    return dynamic_renderables_textures.at("ironHelmetSprite");
}

std::string SdlTextureManager::findTextureId(const std::string &id) {
    std::string texture_id = "player";
    for (auto & renderable_id : RENDERABLES_TEXTURES_ID){
        if (id.find(renderable_id) != std::string::npos){
            texture_id = renderable_id;
        }
    }
    return texture_id;
}

SdlTexture& SdlTextureManager::getTexture(const std::string &texture_id) {
    return dynamic_renderables_textures.at(texture_id);
}

SdlTexture& SdlTextureManager::getSpriteTexture(const std::string &texture_id) {
    return dynamic_renderables_textures.at(texture_id + "Sprite");
}

void SdlTextureManager::renderNPC(const std::string &texture_id, const int x, const int y, e_body_orientation e) {
    SDL_Rect body_orientation_clips[TOTAL_ORIENTATIONS];
    SdlTexture& bodySpriteSheetTexture = this->getTexture(texture_id);
    for (int i = 0; i < TOTAL_ORIENTATIONS ; ++i) {
        body_orientation_clips[i] = {0, i * bodySpriteSheetTexture.getHeight(),
                                     bodySpriteSheetTexture.getWidth(), bodySpriteSheetTexture.getHeight()};
    }
    bodySpriteSheetTexture.render(x, y, &body_orientation_clips[e]);
}


void SdlTextureManager::renderPC(const t_player_appearance& appearance, const int pos_x,
                                 const int pos_y, SdlCamera& camera,
                                 e_body_orientation body, e_head_orientation head){

    SDL_Rect head_orientation_clips[TOTAL_ORIENTATIONS];
    SdlTexture& headSpriteSheetTexture = this->getSpriteTexture(appearance.head);
    //SdlTexture& helmetSpriteSheetTexture = this->getSpriteTexture(appearance.helmet);
    for (int i = 0; i < TOTAL_ORIENTATIONS ; ++i) {
        head_orientation_clips[i] = {i*headSpriteSheetTexture.getWidth(),
                                     0, headSpriteSheetTexture.getWidth(),
                                     headSpriteSheetTexture.getHeight()};
    }
    std::string armour = appearance.armour;
    if(appearance.armour == "none"){
        armour = "defaultArmour";
    }
    SdlTexture& armourSpriteSheetTexture = this->getSpriteTexture(armour);
    SdlTexture& weaponSpriteSheetTexture = this->getSpriteTexture(appearance.weapon);
    SdlTexture& shieldSpriteSheetTexture = this->getSpriteTexture(appearance.shield);

    SDL_Rect armour_orientation_clips[TOTAL_ORIENTATIONS];
    SDL_Rect weapon_orientation_clips[TOTAL_ORIENTATIONS];
    SDL_Rect shield_orientation_clips[TOTAL_ORIENTATIONS];

    for (int i = 0; i < TOTAL_ORIENTATIONS ; ++i) {
        armour_orientation_clips[i] = {0, i * armourSpriteSheetTexture.getHeight(),
                                      armourSpriteSheetTexture.getWidth(),
                                      armourSpriteSheetTexture.getHeight()};
        weapon_orientation_clips[i] = {0, i*weaponSpriteSheetTexture.getHeight(),
                                       weaponSpriteSheetTexture.getWidth(),
                                       weaponSpriteSheetTexture.getHeight()};
        shield_orientation_clips[i] = {0, i*shieldSpriteSheetTexture.getHeight(),
                                       shieldSpriteSheetTexture.getWidth(),
                                       shieldSpriteSheetTexture.getHeight()};
    }

    int body_offset_y = armourSpriteSheetTexture.getHeight() - 32;

    headSpriteSheetTexture.render((pos_x + (armourSpriteSheetTexture.getWidth() - headSpriteSheetTexture.getWidth() )/ 2) - camera.getX(),
                                   (pos_y - headSpriteSheetTexture.getHeight() - body_offset_y) - camera.getY(),
                                   &head_orientation_clips[head]);
    armourSpriteSheetTexture.render(pos_x - camera.getX(),
                                     (pos_y - body_offset_y) - camera.getY(),
                                     &armour_orientation_clips[body]);
    weaponSpriteSheetTexture.render(pos_x - camera.getX(),
                                     (pos_y - body_offset_y) - camera.getY(),
                                     &weapon_orientation_clips[body]);
    shieldSpriteSheetTexture.render(pos_x - camera.getX(),
                                     (pos_y - body_offset_y) - camera.getY(),
                                     &shield_orientation_clips[body]);
}