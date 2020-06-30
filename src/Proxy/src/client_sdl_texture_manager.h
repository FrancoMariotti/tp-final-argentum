//
// Created by agustin on 30/6/20.
//

#ifndef ARGENTUM_CLIENT_TEXTURE_MANAGER_H
#define ARGENTUM_CLIENT_TEXTURE_MANAGER_H


#include <string>
#include <map>
#include <vector>

class SdlTexture;
class SdlWindow;
class SdlTextureManager {
private:
    const int HEAD_WIDTH = 17;
    const int HEAD_HEIGHT = 16;

    std::map<std::string, SdlTexture> dynamic_renderables_textures;

    const std::vector<std::string> RENDERABLES_TEXTURES_ID{"goblin","skeleton","zombie","spider"};

public:
    explicit SdlTextureManager(const SdlWindow& window);

    SdlTexture &initHead();

    SdlTexture &initArmour();

    SdlTexture &initShield();

    SdlTexture &initWeapon();

    std::string findTextureId(const std::string &id);

    SdlTexture &getTexture(const std::string &texture_id);

    SdlTexture &getSpriteTexture(const std::string &texture_id);
};


#endif //ARGENTUM_CLIENT_TEXTURE_MANAGER_H
