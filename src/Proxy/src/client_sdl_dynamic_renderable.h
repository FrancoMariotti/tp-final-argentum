//
// Created by agustin on 24/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
#define ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H


#include <SDL2/SDL_rect.h>

class SdlTexture;
class SdlCamera;
class SdlDynamicRenderable {
protected:
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

private:
    SdlTexture& bodySpriteSheetTexture;


public:
    SdlDynamicRenderable(const int x, const int y, SdlTexture &bodyTexture);

    void update(const int vel_x, const int vel_y, SdlCamera &camera);

    virtual void render(SdlCamera& camera);
};

class SdlPlayableCharacter : public SdlDynamicRenderable {
private:
    SdlTexture& headSpriteSheetTexture;
    SdlTexture& helmetSpriteSheetTexture;
    SdlTexture& weaponSpriteSheetTexture;
    SdlTexture& shieldSpriteSheetTexture;

    SDL_Rect head_orientation_clips[TOTAL_ORIENTATIONS];
    SDL_Rect helmet_orientation_clips[TOTAL_ORIENTATIONS];
    SDL_Rect weapon_orientation_clips[TOTAL_ORIENTATIONS];
    SDL_Rect shield_orientation_clips[TOTAL_ORIENTATIONS];

public:
    SdlPlayableCharacter(const int x, const int y, SdlTexture &bodySpriteSheetTexture,
            SdlTexture& headSpriteSheetTexture,
            SdlTexture& helmetSpriteSheetTexture,
            SdlTexture& weaponSpriteSheetTexture,
            SdlTexture& shieldSpriteSheetTexture);

    void render(SdlCamera &camera) override;
};


#endif //ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
