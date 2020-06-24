//
// Created by agustin on 24/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
#define ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H


#include "client_sdl_texture.h"
class SdlCamera;
class SdlDynamicRenderable {
private:
    SdlTexture bodySpriteSheetTexture;

    int pos_x;
    int pos_y;

    enum orientation{
        FRONT,
        BACK,
        LEFT,
        RIGHT,
        TOTAL_ORIENTATIONS,
    };
    SDL_Rect orientation_clips[TOTAL_ORIENTATIONS];
    enum orientation e_current_orientation;

public:
    SdlDynamicRenderable(int x, int y, int width, int height, const std::string &id,
                         const SdlWindow &window);

    void update(const int vel_x, const int vel_y);

    void render(SdlCamera& camera);
};




#endif //ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
