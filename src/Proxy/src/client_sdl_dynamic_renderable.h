//
// Created by agustin on 24/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
#define ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H


#include <SDL2/SDL_rect.h>
#include "client_sdl_texture_manager.h"

class SdlTexture;
class SdlCamera;
class SdlDynamicRenderable {
private:
    int pos_x;
    int pos_y;
    const std::string texture_id;
    SdlTextureManager& textureManager;
    SdlTextureManager::e_body_orientation body_or;

public:
    SdlDynamicRenderable(int x, int y, SdlTextureManager &textureManager,
            std::string texture_id);

    void update(int new_x, int new_y, SdlCamera &camera);

    virtual void render(const SdlCamera& camera);
};


#endif //ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
