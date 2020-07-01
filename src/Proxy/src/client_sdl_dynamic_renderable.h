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

    enum e_head_orientation{
        FRONT_HEAD_SPRITE,
        RIGHT_HEAD_SPRITE,
        LEFT_HEAD_SPRITE,
        BACK_HEAD_SPRITE,
        TOTAL_HEAD_SPRITE
    };

    enum orientation{
        FRONT,
        BACK,
        LEFT,
        RIGHT,
        TOTAL_ORIENTATIONS,
    };
    SDL_Rect body_orientation_clips[TOTAL_ORIENTATIONS];
    enum orientation e_body_orientation;
    enum e_head_orientation e_face_orientation;

private:
    SdlTexture& bodySpriteSheetTexture;


public:
    SdlDynamicRenderable(int x, int y, SdlTexture &bodyTexture);

    void update(int new_x, int new_y, SdlCamera &camera);

    virtual void render(SdlCamera& camera);
};

class SdlPlayableCharacter : public SdlDynamicRenderable {
private:
    SdlTexture& headSpriteSheetTexture;
    SdlTexture& helmetSpriteSheetTexture;
    SdlTexture& weaponSpriteSheetTexture;
    SdlTexture& shieldSpriteSheetTexture;

    SDL_Rect head_orientation_clips[TOTAL_ORIENTATIONS];
    SDL_Rect weapon_orientation_clips[TOTAL_ORIENTATIONS];
    SDL_Rect shield_orientation_clips[TOTAL_ORIENTATIONS];

public:
    SdlPlayableCharacter(int x, int y, SdlTexture &bodySpriteSheetTexture,
            SdlTexture& headSpriteSheetTexture,
            SdlTexture& helmetSpriteSheetTexture,
            SdlTexture& weaponSpriteSheetTexture,
            SdlTexture& shieldSpriteSheetTexture);

    void update(int new_x, int new_y, SdlCamera &camera);

    void render(SdlCamera &camera) override;
};


#endif //ARGENTUM_CLIENT_SDL_DYNAMIC_RENDERABLE_H
