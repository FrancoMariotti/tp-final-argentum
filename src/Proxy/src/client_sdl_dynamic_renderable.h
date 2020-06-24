//
// Created by agustin on 24/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
#define ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H


#include <SDL2/SDL_rect.h>

class SdlTexture;
class SdlCamera;
class SdlDynamicRenderable {
private:
    SdlTexture& bodySpriteSheetTexture;

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
    SdlDynamicRenderable(const int x, const int y, SdlTexture &bodyTexture);

    void update(const int vel_x, const int vel_y, SdlCamera &camera);

    void render(SdlCamera& camera);
};




#endif //ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
