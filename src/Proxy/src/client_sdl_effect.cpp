//
// Created by agustin on 5/7/20.
//

#include <SDL2/SDL_rect.h>
#include "client_sdl_effect.h"
#include "client_sdl_texture.h"
#include "client_sdl_audio_manager.h"

SdlEffect::SdlEffect(SdlTexture& effectSpriteSheetTexture, std::string effect_id, SdlAudioManager& audioManager) :
        effectSpriteSheetTexture(&effectSpriteSheetTexture),
        audioManager(&audioManager),
        EFFECT_ID(effect_id),
        animation_frame(0),
        keep_animating(true){
    if(EFFECT_ID == "explosion"){
        sprites_per_row = 5;
        total_frames = 10;
    } else if (EFFECT_ID == "missile"){
        sprites_per_row = 8;
        total_frames = 8;
    } else if (EFFECT_ID == "heal"){
        sprites_per_row = 6;
        total_frames = 6;
    } else if (EFFECT_ID == "magicArrow"){
        sprites_per_row = 5;
        total_frames = 5;
    }
}

void SdlEffect::render(const int x, const int y){
    if(animation_frame == 0){
        audioManager->playSound(EFFECT_ID, 0);
    }
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

bool SdlEffect::isFinish() const{
    return !keep_animating;
}