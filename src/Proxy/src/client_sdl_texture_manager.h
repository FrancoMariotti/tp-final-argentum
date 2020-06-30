//
// Created by agustin on 30/6/20.
//

#ifndef ARGENTUM_CLIENT_TEXTURE_MANAGER_H
#define ARGENTUM_CLIENT_TEXTURE_MANAGER_H


#include <string>
#include <map>

class SdlTexture;
class SdlWindow;
class SdlTextureManager {
private:
    std::map<std::string, SdlTexture> dynamic_renderables_textures;

    const int HEAD_WIDTH = 17;
    const int HEAD_HEIGHT = 16;

public:
    explicit SdlTextureManager(const SdlWindow& window);

    SdlTexture &initHead();

    SdlTexture &initArmour();

    SdlTexture &initShield();

    SdlTexture &initWeapon();
};


#endif //ARGENTUM_CLIENT_TEXTURE_MANAGER_H
