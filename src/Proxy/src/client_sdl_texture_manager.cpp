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
    this->dynamic_renderables_textures.emplace(std::make_pair("axeSprite",
                                                              SdlTexture(22, 48, "../../Proxy/items/axeSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("swordSprite",
                                                              SdlTexture(22, 48, "../../Proxy/items/swordSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("defaultArmourSprite",
                                                              SdlTexture(24, 46, "../../Proxy/items/defaultArmourSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("ironArmourSprite",
                                                              SdlTexture(24, 46, "../../Proxy/items/ironArmourSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("humanHeadSprite",
                                                              SdlTexture(HEAD_WIDTH, HEAD_HEIGHT, "../../Proxy/assets/humanHeadSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("ironHelmetSprite",
                                                              SdlTexture(HEAD_WIDTH, HEAD_HEIGHT, "../../Proxy/items/ironHelmetSprite.png", window)));
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

