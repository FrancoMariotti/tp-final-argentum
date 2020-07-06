//
// Created by agustin on 5/7/20.
//

#ifndef ARGENTUM_CLIENT_SDL_EFFECT_H
#define ARGENTUM_CLIENT_SDL_EFFECT_H


#include <string>

class SdlTexture;
class SdlEffect {
private:
    SdlTexture* effectSpriteSheetTexture;
    int sprites_per_row;
    int total_frames;
    int animation_frame;
    bool keep_animating;
public:
    SdlEffect(SdlTexture& effectSpriteSheetTexture, int sprites_per_row, int total_frames);

    void render(const int x, const int y);

    void setEffect(SdlTexture *effectTexture, int sprites_per_row, int frames);
};


#endif //ARGENTUM_CLIENT_SDL_EFFECT_H
