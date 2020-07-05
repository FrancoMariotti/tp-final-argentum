//
// Created by agustin on 5/7/20.
//

#ifndef ARGENTUM_CLIENT_SDL_EFFECT_H
#define ARGENTUM_CLIENT_SDL_EFFECT_H


class SdlTexture;
class SdlEffect {
private:
    SdlTexture& effectSpriteSheetTexture;
    const int SPRITES_PER_ROW;
    const int TOTAL_FRAMES;
    int animation_frame;
    bool is_animating;
    bool keep_animating;
public:
    SdlEffect(SdlTexture& effectSpriteSheetTexture, int sprites_per_row, int total_frames);

    void render(const int x, const int y);
};


#endif //ARGENTUM_CLIENT_SDL_EFFECT_H
