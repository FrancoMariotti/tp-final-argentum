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


class SdlTexture;
class SdlWindow;
class SdlTextureManager {
private:
    const int HEAD_WIDTH = 17;
    const int HEAD_HEIGHT = 14;
    const int ARMOUR_WIDTH = 24;
    const int ARMOUR_HEIGHT = 45;

    const std::string ASSETS_PATH = "../../Proxy/assets/";
    const std::string ITEMS_PATH = "../../Proxy/items/";
    const std::string SPRITE_SUFFIX = "Sprite";
    std::map<std::string, SdlTexture> dynamic_renderables_textures;
    const std::vector<std::string> RENDERABLES_TEXTURES_ID{"goblin","skeleton","zombie",
                                                           "spider","banker","priest","merchant"};

    std::vector<SDL_Rect> WALKING_ANIMATION_SPRITE;
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
};


#endif //ARGENTUM_CLIENT_TEXTURE_MANAGER_H
