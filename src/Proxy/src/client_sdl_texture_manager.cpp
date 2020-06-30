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
                                                              SdlTexture(22, 48, "../../Proxy/items/sAxe.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("ironArmourSprite",
                                                              SdlTexture(24, 46, "../../Proxy/items/sIronArmour.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("humanHeadSprite",
                                                              SdlTexture(18, 18, "../../Proxy/assets/humanHeadSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("ironHelmetSprite",
                                                              SdlTexture(18, 18, "../../Proxy/items/ironHelmetSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("ironShieldSprite",
                                                              SdlTexture(25, 44, "../../Proxy/items/ironShieldSprite.png", window)));
}

SdlTexture& SdlTextureManager::initHead(){
    return dynamic_renderables_textures.at("humanHeadSprite");
}

SdlTexture& SdlTextureManager::initArmour(){
    return dynamic_renderables_textures.at("ironArmourSprite");
}
