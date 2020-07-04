//
// Created by agustin on 30/6/20.
//

#ifndef ARGENTUM_CLIENT_TEXTURE_MANAGER_H
#define ARGENTUM_CLIENT_TEXTURE_MANAGER_H


#include <string>
#include <map>
#include <vector>
#include <SDL2/SDL_rect.h>
#include "client_sdl_camera.h"

class SdlTimer;
class SdlTexture;
class SdlWindow;
class SdlTextureManager {
private:
    const int HEAD_WIDTH = 17;
    const int HEAD_HEIGHT = 14;
    const int ARMOUR_WIDTH = 25;
    const int ARMOUR_HEIGHT = 45;
    const int PNG_OFFSET_Y = 4;

    const std::string ASSETS_PATH = "../../Proxy/assets/";
    const std::string ITEMS_PATH = "../../Proxy/items/";
    const std::string SPRITE_SUFFIX = "Sprite";
    std::map<std::string, SdlTexture> dynamic_renderables_textures;
    const std::vector<std::string> RENDERABLES_TEXTURES_ID{"goblin","skeleton","zombie",
                                                           "spider","banker","priest","merchant"};

public:
    enum e_body_orientation{
        FRONT,
        BACK,
        LEFT,
        RIGHT,
        TOTAL_ORIENTATIONS,
    };
    enum e_head_orientation{
        FRONT_HEAD_SPRITE,
        RIGHT_HEAD_SPRITE,
        LEFT_HEAD_SPRITE,
        BACK_HEAD_SPRITE,
        TOTAL_HEAD_SPRITE
    };

    typedef struct t_player_appearance{
        std::string head;
        std::string helmet;
        std::string armour;
        std::string weapon;
        std::string shield;
    }t_player_appearance;
    explicit SdlTextureManager(const SdlWindow& window);

    std::string findTextureId(const std::string &id);

    SdlTexture &getTexture(const std::string &texture_id);

    SdlTexture &getSpriteTexture(const std::string &texture_id);

    void renderNPC(const std::string &texture_id, int x, int y, e_body_orientation e);

    void renderPC(const t_player_appearance &appearance, int pos_x, int pos_y,const SdlCamera &camera,
                  e_body_orientation body, e_head_orientation head);

    void renderMovingPC(const t_player_appearance &appearance, int of_x, int of_y, const SdlCamera &camera,
                        int old_x, int old_y, int animation_frame, e_body_orientation body_or,
                        e_head_orientation head_or);

    void renderStillPC(const t_player_appearance &appearance, const int pos_x, const int pos_y, const SdlCamera &camera,
                       e_body_orientation body, e_head_orientation head);

    int headX(const int tile_size, const int head_w) const;

    int armourX(const int tile_size, int armour_w) const;

    int armourY(const int tile_size, int armour_h, int png_offset_y) const;
};


#endif //ARGENTUM_CLIENT_TEXTURE_MANAGER_H
