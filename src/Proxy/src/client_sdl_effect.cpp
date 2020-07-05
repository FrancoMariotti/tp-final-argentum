//
// Created by agustin on 5/7/20.
//

#include <SDL2/SDL_rect.h>
#include "client_sdl_effect.h"
#include "client_sdl_texture.h"

SdlEffect::SdlEffect(SdlTexture &effectSpriteSheetTexture, const int sprites_per_row, const int total_frames) :
        effectSpriteSheetTexture(effectSpriteSheetTexture),
        SPRITES_PER_ROW(sprites_per_row),
        TOTAL_FRAMES(total_frames),
        animation_frame(0),
        is_animating(false),
        keep_animating(true)
        {}

void SdlEffect::render(const int x, const int y){
    if(keep_animating){
        int col = animation_frame % 5;
        int row = animation_frame / 5;
        SDL_Rect effect_clip{col * effectSpriteSheetTexture.getWidth(), row,
                             effectSpriteSheetTexture.getWidth(), effectSpriteSheetTexture.getHeight()};
        effectSpriteSheetTexture.render(x, y, &effect_clip);
        animation_frame++;
        if(animation_frame >= TOTAL_FRAMES){
            keep_animating = false;
        }
    }
}