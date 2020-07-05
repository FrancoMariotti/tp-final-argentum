//
// Created by agustin on 30/6/20.
//

#include "client_sdl_texture_manager.h"
#include "client_sdl_texture.h"

SdlTextureManager::SdlTextureManager(const SdlWindow &window) {
    this->dynamic_renderables_textures.emplace(std::make_pair("spider",
            SdlTexture(54, 35, "../../Proxy/assets/spiderSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("skeleton",
            SdlTexture(26, 52, "../../Proxy/assets/skeletonSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("zombie",
            SdlTexture(24, 46, "../../Proxy/assets/zombieSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("goblin",
            SdlTexture(24, 32, "../../Proxy/assets/goblinSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("merchant",
            SdlTexture(26, 46, ASSETS_PATH + "merchantSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("priest",
            SdlTexture(26, 46, ASSETS_PATH + "priestSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("banker",
            SdlTexture(26, 48, ASSETS_PATH + "bankerSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("ghostSprite",
            SdlTexture(30, 32, ASSETS_PATH + "ghostSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("noneSprite",
            SdlTexture(1, 1, ITEMS_PATH + "noneSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("swordSprite",
            SdlTexture(24, 45, ITEMS_PATH + "swordSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("axeSprite",
            SdlTexture(22, 48, ITEMS_PATH + "axeSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("hammerSprite",
            SdlTexture(22, 48, ITEMS_PATH + "hammerSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("fresnoWandSprite",
            SdlTexture(22, 48, ITEMS_PATH + "fresnoWandSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("elvenFluteSprite",
            SdlTexture(22, 48, ITEMS_PATH + "elvenFluteSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("knottyStickSprite",
            SdlTexture(22, 48, ITEMS_PATH + "knottyStickSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("crimpStickSprite",
            SdlTexture(22, 48, ITEMS_PATH + "crimpStickSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("commonBowSprite",
            SdlTexture(ARMOUR_WIDTH, ARMOUR_HEIGHT, ITEMS_PATH + "commonBowSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("rareBowSprite",
            SdlTexture(22, 48, ITEMS_PATH + "rareBowSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("defaultArmourSprite",
            SdlTexture(ARMOUR_WIDTH, ARMOUR_HEIGHT, ITEMS_PATH + "defaultArmourSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("leatherArmourSprite",
            SdlTexture(ARMOUR_WIDTH, ARMOUR_HEIGHT, ITEMS_PATH + "leatherArmourSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("ironArmourSprite",
            SdlTexture(ARMOUR_WIDTH, ARMOUR_HEIGHT, ITEMS_PATH + "ironArmourSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("humanHeadSprite",
            SdlTexture(HEAD_WIDTH, HEAD_HEIGHT, "../../Proxy/assets/humanHeadSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("elfHeadSprite",
            SdlTexture(HEAD_WIDTH, HEAD_HEIGHT, "../../Proxy/assets/elfHeadSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("dwarfHeadSprite",
            SdlTexture(HEAD_WIDTH, HEAD_HEIGHT, "../../Proxy/assets/dwarfHeadSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("gnomeHeadSprite",
            SdlTexture(HEAD_WIDTH, HEAD_HEIGHT, "../../Proxy/assets/gnomeHeadSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("hoodSprite",
            SdlTexture(HEAD_WIDTH, HEAD_HEIGHT, "../../Proxy/items/hoodSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("ironHelmetSprite",
            SdlTexture(HEAD_WIDTH, HEAD_HEIGHT, "../../Proxy/items/ironHelmetSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("turtleShellSprite",
            SdlTexture(24, 45, ITEMS_PATH + "turtleShellSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("ironShieldSprite",
            SdlTexture(24, 45, "../../Proxy/items/ironShieldSprite.png", window)));
    this->dynamic_renderables_textures.emplace(std::make_pair("magicHatSprite",
            SdlTexture(HEAD_WIDTH, HEAD_HEIGHT, "../../Proxy/items/magicHatSprite.png", window)));

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

void
SdlTextureManager::renderStillNPC(const std::string &texture_id,
        const int pos_x, const int pos_y, e_body_orientation body_or,
                                  const SdlCamera &camera) {
    SdlTexture& bodySpriteSheetTexture = this->getTexture(texture_id);
    SDL_Rect body_orientation_clip {0,
                                    body_or * bodySpriteSheetTexture.getHeight(),
                                     bodySpriteSheetTexture.getWidth(),
                                     bodySpriteSheetTexture.getHeight()};

    int tile_size = camera.getTileSize();

    int body_x = armourX(tile_size, bodySpriteSheetTexture.getWidth());
    int body_y = armourY(tile_size, bodySpriteSheetTexture.getHeight(), 0);
    bodySpriteSheetTexture.render(pos_x + body_x - camera.getX(),
            pos_y - body_y - camera.getY(), &body_orientation_clip);
}

void
SdlTextureManager::renderMovingNPC(const std::string &texture_id, const int old_x,
        const int old_y, e_body_orientation body_or,
        const int of_x, const int of_y, int animation_frame,const SdlCamera &camera) {
    SdlTexture& bodySpriteSheetTexture = this->getTexture(texture_id);
    if(texture_id == "spider" && animation_frame > 3 ){
        animation_frame = 3;
    }
    SDL_Rect body_orientation_clip {animation_frame * bodySpriteSheetTexture.getWidth(),
                                    body_or * bodySpriteSheetTexture.getHeight(),
                                    bodySpriteSheetTexture.getWidth(), bodySpriteSheetTexture.getHeight()};

    int tile_size = camera.getTileSize();

    int body_x = armourX(tile_size, bodySpriteSheetTexture.getWidth());
    int body_y = armourY(tile_size, bodySpriteSheetTexture.getHeight(), 0);

    int animation_x = getAnimationPosFor(old_x, of_x, animation_frame);
    int animation_y = getAnimationPosFor(old_y, of_y, animation_frame);

    bodySpriteSheetTexture.render(animation_x + body_x - camera.getX(),
            animation_y - body_y - camera.getY(), &body_orientation_clip);
}

void SdlTextureManager::renderStillPC(const t_player_appearance& appearance, const int pos_x,
                                      const int pos_y,const SdlCamera& camera,
                                      e_body_orientation body, e_head_orientation head){
    SdlTexture& headSpriteSheetTexture = this->getSpriteTexture(appearance.head);
    SdlTexture& helmetSpriteSheetTexture = this->getSpriteTexture(appearance.helmet);
    std::string armour = appearance.armour;
    if(appearance.armour == "none"){
        armour = "defaultArmour";
    }
    SdlTexture& armourSpriteSheetTexture = this->getSpriteTexture(armour);
    SdlTexture& weaponSpriteSheetTexture = this->getSpriteTexture(appearance.weapon);
    SdlTexture& shieldSpriteSheetTexture = this->getSpriteTexture(appearance.shield);
    SDL_Rect head_orientation_clip = {head * headSpriteSheetTexture.getWidth(),
                                      0, headSpriteSheetTexture.getWidth(),
                                      headSpriteSheetTexture.getHeight()};
    SDL_Rect armour_orientation_clip = {0, body * armourSpriteSheetTexture.getHeight(),
                                        armourSpriteSheetTexture.getWidth(),
                                        armourSpriteSheetTexture.getHeight()};
    SDL_Rect weapon_orientation_clip = {0, body * weaponSpriteSheetTexture.getHeight(),
                                        weaponSpriteSheetTexture.getWidth(),
                                        weaponSpriteSheetTexture.getHeight()};
    SDL_Rect shield_orientation_clip = {0, body * shieldSpriteSheetTexture.getHeight(),
                                        shieldSpriteSheetTexture.getWidth(),
                                        shieldSpriteSheetTexture.getHeight()};

    const int tile_size = camera.getTileSize();

    int head_w = headSpriteSheetTexture.getWidth();
    int head_h = headSpriteSheetTexture.getHeight();
    int armour_w = armourSpriteSheetTexture.getWidth();
    int armour_h = armourSpriteSheetTexture.getHeight();

    /*Variables arbitrarias para corregir la division de entero y eliminar
     * parte del recorte del png*/

    int head_x = headX(tile_size, head_w);
    int armour_x = armourX(tile_size, armour_w);
    int armour_y = armourY(tile_size,armour_h, PNG_OFFSET_Y);

    headSpriteSheetTexture.render(pos_x + head_x - camera.getX(),
                                  (pos_y - head_h - armour_y + PNG_OFFSET_Y) - camera.getY(),
                                  &head_orientation_clip);
    helmetSpriteSheetTexture.render(pos_x + head_x - camera.getX(),
                                    (pos_y - head_h - armour_y + PNG_OFFSET_Y) - camera.getY(),
                                    &head_orientation_clip);
    armourSpriteSheetTexture.render(pos_x + armour_x - camera.getX(),
                                    (pos_y - armour_y) - camera.getY(),
                                    &armour_orientation_clip);
    weaponSpriteSheetTexture.render(pos_x + armour_x - camera.getX(),
                                    (pos_y - armour_y) - camera.getY(),
                                    &weapon_orientation_clip);
    shieldSpriteSheetTexture.render(pos_x + armour_x - camera.getX(),
                                    (pos_y - armour_y) - camera.getY(),
                                    &shield_orientation_clip);
}

void
SdlTextureManager::renderMovingPC(const t_player_appearance &appearance, int of_x, int of_y, const SdlCamera &camera,
                                  int old_x, int old_y, int animation_frame, e_body_orientation body_or,
                                  e_head_orientation head_or) {
    SdlTexture& headSpriteSheetTexture = this->getSpriteTexture(appearance.head);
    SdlTexture& helmetSpriteSheetTexture = this->getSpriteTexture(appearance.helmet);
    std::string armour = appearance.armour;
    if(appearance.armour == "none"){
        armour = "defaultArmour";
    }
    if(appearance.armour == "ghost" && animation_frame > 2 ){
        animation_frame = 2;
    }
    SdlTexture& armourSpriteSheetTexture = this->getSpriteTexture(armour);
    SdlTexture& weaponSpriteSheetTexture = this->getSpriteTexture(appearance.weapon);
    SdlTexture& shieldSpriteSheetTexture = this->getSpriteTexture(appearance.shield);


    SDL_Rect head_orientation_clip {head_or * headSpriteSheetTexture.getWidth(),
                                    0, headSpriteSheetTexture.getWidth(),
                                    headSpriteSheetTexture.getHeight()};
    SDL_Rect armour_orientation_clip {animation_frame * armourSpriteSheetTexture.getWidth(),
                                      body_or * armourSpriteSheetTexture.getHeight(),
                                      armourSpriteSheetTexture.getWidth(),
                                      armourSpriteSheetTexture.getHeight()};
    SDL_Rect weapon_orientation_clip {animation_frame * weaponSpriteSheetTexture.getWidth() ,
                                      body_or * weaponSpriteSheetTexture.getHeight(),
                                      weaponSpriteSheetTexture.getWidth(),
                                      weaponSpriteSheetTexture.getHeight()};
    SDL_Rect shield_orientation_clip {animation_frame * shieldSpriteSheetTexture.getWidth(),
                                      body_or * shieldSpriteSheetTexture.getHeight(),
                                      shieldSpriteSheetTexture.getWidth(),
                                      shieldSpriteSheetTexture.getHeight()};

    const int tile_size = camera.getTileSize();

    int head_w = headSpriteSheetTexture.getWidth();
    int head_h = headSpriteSheetTexture.getHeight();
    int armour_w = armourSpriteSheetTexture.getWidth();
    int armour_h = armourSpriteSheetTexture.getHeight();

    /*Variables arbitrarias para corregir la division de entero y eliminar
     * parte del recorte del png*/
    int png_offset_y = 4;
    //int png_offset_x = 1;
    int head_x = this->headX(tile_size, head_w);
    int armour_x = this->armourX(tile_size, armour_w);
    int armour_y = this->armourY(tile_size, armour_h, png_offset_y);

    int animation_x = old_x + (of_x/4) * animation_frame;
    int animation_y = old_y + (of_y/4) * animation_frame;

    headSpriteSheetTexture.render(animation_x + head_x - camera.getX(),
                                  (animation_y - head_h - armour_y + png_offset_y) - camera.getY(),
                                  &head_orientation_clip);
    helmetSpriteSheetTexture.render(animation_x + head_x - camera.getX(),
                                    (animation_y - head_h - armour_y + png_offset_y) - camera.getY(),
                                    &head_orientation_clip);
    armourSpriteSheetTexture.render(animation_x + armour_x - camera.getX(),
                                    animation_y - armour_y - camera.getY(),
                                    &armour_orientation_clip);
    weaponSpriteSheetTexture.render(animation_x + armour_x - camera.getX(),
                                    (animation_y - armour_y) - camera.getY(),
                                    &weapon_orientation_clip);
    shieldSpriteSheetTexture.render(animation_x + armour_x - camera.getX(),
                                    (animation_y - armour_y) - camera.getY(),
                                    &shield_orientation_clip);
}

int SdlTextureManager::getAnimationPosFor(const int old, const int off, int animation_frame) const {
    int animation_pos = old + (off / 4) * animation_frame;
    return animation_pos;
}

int SdlTextureManager::headX(const int tile_size, const int head_w) const {
    return ((tile_size - head_w) / 2);
}

int SdlTextureManager::armourY(const int tile_size, int armour_h, int png_offset_y) const {
    int armour_y = (armour_h - tile_size / 2) - png_offset_y;
    return armour_y;
}

int SdlTextureManager::armourX(const int tile_size, int armour_w) const {
    int armour_x = (tile_size - armour_w) / 2;
    return armour_x;
}
