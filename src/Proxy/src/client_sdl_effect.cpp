//
// Created by agustin on 5/7/20.
//

#include <SDL2/SDL_rect.h>
#include "client_sdl_effect.h"
#include "client_sdl_texture.h"

SdlEffect::SdlEffect(SdlTexture &effectSpriteSheetTexture, const int sprites_per_row, const int total_frames) :
        effectSpriteSheetTexture(&effectSpriteSheetTexture),
        sprites_per_row(sprites_per_row),
        total_frames(total_frames),
        animation_frame(0),
        keep_animating(true)
        {}

void SdlEffect::render(const int x, const int y){
    if(keep_animating){
        int col = animation_frame % sprites_per_row;
        int row = animation_frame / sprites_per_row;
        SDL_Rect effect_clip{col * effectSpriteSheetTexture->getWidth(), row,
                             effectSpriteSheetTexture->getWidth(), effectSpriteSheetTexture->getHeight()};
        effectSpriteSheetTexture->render(x, y, &effect_clip);
        animation_frame++;
        if(animation_frame >= total_frames){
            keep_animating = false;
        }
    }
}

/*Seteo un nuevo efecto completamente reemplazando al anterior*/
void SdlEffect::setEffect(SdlTexture *effectTexture, int new_sprites_per_row, int frames) {
    effectSpriteSheetTexture = effectTexture;
    keep_animating = true;
    animation_frame = 0;
    sprites_per_row = new_sprites_per_row;
    total_frames = frames;
}
