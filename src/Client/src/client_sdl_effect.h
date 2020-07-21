//
// Created by agustin on 5/7/20.
//

#ifndef ARGENTUM_CLIENT_SDL_EFFECT_H
#define ARGENTUM_CLIENT_SDL_EFFECT_H


#include <string>

class SdlAudioManager;
class SdlTexture;
class SdlEffect {
private:
    /*Son punteros por problemas con el erase(iterator) al usar referencias*/
    SdlTexture* effectSpriteSheetTexture;
    SdlAudioManager* audioManager;
    std::string EFFECT_ID;
    int sprites_per_row;
    int total_frames;
    int animation_frame;
    int width;
    int height;
    bool keep_animating;
public:
    SdlEffect(SdlTexture& effectSpriteSheetTexture, std::string effect_id, SdlAudioManager& audioManager);

    void render(int x, int y);

    bool isFinish() const;
};


#endif //ARGENTUM_CLIENT_SDL_EFFECT_H
