//
// Created by agustin on 30/6/20.
//

#include "client_sdl_texture_manager.h"
#include "client_sdl_texture.h"
#include "client_sdl_player.h"


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

void SdlTextureManager::renderNPC(const std::string &texture_id, const int x, const int y, e_body_orientation e) {
    SDL_Rect body_orientation_clips[TOTAL_ORIENTATIONS];
    SdlTexture& bodySpriteSheetTexture = this->getTexture(texture_id);
    for (int i = 0; i < TOTAL_ORIENTATIONS ; ++i) {
        body_orientation_clips[i] = {0, i * bodySpriteSheetTexture.getHeight(),
                                     bodySpriteSheetTexture.getWidth(), bodySpriteSheetTexture.getHeight()};
    }
    int body_x = (32 - bodySpriteSheetTexture.getWidth()) / 2;
    int body_y = (bodySpriteSheetTexture.getHeight() - (32 / 2));
    bodySpriteSheetTexture.render(x + body_x, y - body_y, &body_orientation_clips[e]);
}


void SdlTextureManager::renderPC(const t_player_appearance& appearance, const int pos_x,
                                 const int pos_y,const SdlCamera& camera,
                                 e_body_orientation body, e_head_orientation head){

    SDL_Rect head_orientation_clips[TOTAL_ORIENTATIONS];
    SdlTexture& headSpriteSheetTexture = this->getSpriteTexture(appearance.head);
    SdlTexture& helmetSpriteSheetTexture = this->getSpriteTexture(appearance.helmet);
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
        weapon_orientation_clips[i] = {0, i * weaponSpriteSheetTexture.getHeight(),
                                       weaponSpriteSheetTexture.getWidth(),
                                       weaponSpriteSheetTexture.getHeight()};
        shield_orientation_clips[i] = {0, i * shieldSpriteSheetTexture.getHeight(),
                                       shieldSpriteSheetTexture.getWidth(),
                                       shieldSpriteSheetTexture.getHeight()};
    }

    const int tile_size = camera.getTileSize();

    int head_w = headSpriteSheetTexture.getWidth();
    int head_h = headSpriteSheetTexture.getHeight();
    int armour_w = armourSpriteSheetTexture.getWidth();
    int armour_h = armourSpriteSheetTexture.getHeight();

    /*Variables arbitrarias para corregir la division de entero y eliminar
     * parte del recorte del png*/
    int png_offset_y = 4;
    int png_offset_x = 1;

    int head_x = ((tile_size - head_w) / 2) + png_offset_x;
    int armour_x = (tile_size - armour_w) / 2;
    int armour_y = (armour_h - tile_size / 2) - png_offset_y;

    headSpriteSheetTexture.render(pos_x + head_x - camera.getX(),
                                   (pos_y - head_h - armour_y + png_offset_y) - camera.getY(),
                                   &head_orientation_clips[head]);
    helmetSpriteSheetTexture.render(pos_x + head_x - camera.getX(),
                                  (pos_y - head_h - armour_y + png_offset_y) - camera.getY(),
                                  &head_orientation_clips[head]);
    armourSpriteSheetTexture.render(pos_x + armour_x - camera.getX(),
                                     (pos_y - armour_y) - camera.getY(),
                                     &armour_orientation_clips[body]);
    weaponSpriteSheetTexture.render(pos_x + armour_x - camera.getX(),
                                     (pos_y - armour_y) - camera.getY(),
                                     &weapon_orientation_clips[body]);
    shieldSpriteSheetTexture.render(pos_x + armour_x - camera.getX(),
                                     (pos_y - armour_y) - camera.getY(),
                                     &shield_orientation_clips[body]);
}