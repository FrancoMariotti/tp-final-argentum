//
// Created by agustin on 24/6/20.
//

#include "client_sdl_dynamic_renderable.h"
#include "client_sdl_camera.h"
#include "client_sdl_texture.h"

SdlDynamicRenderable::SdlDynamicRenderable(const int x, const int y, SdlTexture &bodyTexture) :
        pos_x(x),
        pos_y(y),
        body_orientation_clips{{0, 0, 0, 0}, {0, 0, 0, 0},
                               {0, 0, 0, 0}, {0, 0, 0, 0}},
        e_body_orientation(FRONT),
        e_face_orientation(FRONT_HEAD_SPRITE),
        bodySpriteSheetTexture(bodyTexture){
    /**Deber ia hacer un map que tenga un id y orientation_clips[4] asi resuelvo tod por id*/
    for (int i = 0; i < TOTAL_ORIENTATIONS ; ++i) {
        body_orientation_clips[i] = {0, i * bodyTexture.getHeight(), bodyTexture.getWidth(), bodyTexture.getHeight()};
    }
}

void SdlDynamicRenderable::update(const int new_x, const int new_y, SdlCamera &camera) {
    int old_x = pos_x;
    int old_y = pos_y;
    pos_x = camera.toPixels(new_x);
    pos_y = camera.toPixels(new_y);
    if(pos_x > old_x){
        e_body_orientation = RIGHT;
        e_face_orientation = RIGHT_HEAD_SPRITE;
    } else if(pos_x < old_x){
        e_body_orientation = LEFT;
        e_face_orientation = LEFT_HEAD_SPRITE;
    } else if(pos_y > old_y){
        e_body_orientation = FRONT;
        e_face_orientation = FRONT_HEAD_SPRITE;
    } else if(pos_y < old_y){
        e_body_orientation = BACK;
        e_face_orientation = BACK_HEAD_SPRITE;
    }
}

void SdlDynamicRenderable::render(SdlCamera& camera){
    bodySpriteSheetTexture.render(pos_x - camera.getX(), pos_y - camera.getY(), &body_orientation_clips[e_body_orientation]);
}

SdlPlayableCharacter::SdlPlayableCharacter(const int x, const int y, SdlTexture &bodySpriteSheetTexture,
       SdlTexture &headSpriteSheetTexture, SdlTexture &helmetSpriteSheetTexture,
       SdlTexture &weaponSpriteSheetTexture, SdlTexture &shieldSpriteSheetTexture) :
       SdlDynamicRenderable(x,y, bodySpriteSheetTexture),
       headSpriteSheetTexture(headSpriteSheetTexture),
       helmetSpriteSheetTexture(helmetSpriteSheetTexture),
       weaponSpriteSheetTexture(weaponSpriteSheetTexture),
       shieldSpriteSheetTexture(shieldSpriteSheetTexture){

    for (int i = 0; i < TOTAL_ORIENTATIONS ; ++i) {
        head_orientation_clips[i] = {i * headSpriteSheetTexture.getHeight(), 0, headSpriteSheetTexture.getWidth(), headSpriteSheetTexture.getHeight()};
        weapon_orientation_clips[i] = {0, i * weaponSpriteSheetTexture.getHeight(), weaponSpriteSheetTexture.getWidth(), weaponSpriteSheetTexture.getHeight()};
        shield_orientation_clips[i] = {0, i*shieldSpriteSheetTexture.getHeight(), shieldSpriteSheetTexture.getWidth(), shieldSpriteSheetTexture.getHeight()};
    }
}

void SdlPlayableCharacter::update(int new_x, int new_y, SdlCamera &camera) {
    SdlDynamicRenderable::update(new_x, new_y, camera);
}

void SdlPlayableCharacter::render(SdlCamera& camera){
    SdlDynamicRenderable::render(camera);
    headSpriteSheetTexture.render(pos_x - camera.getX(), pos_y - camera.getY(), &head_orientation_clips[e_face_orientation]);
    helmetSpriteSheetTexture.render(pos_x - camera.getX(), pos_y - camera.getY(), &head_orientation_clips[e_face_orientation]);
    weaponSpriteSheetTexture.render(pos_x - camera.getX(), pos_y - camera.getY(), &weapon_orientation_clips[e_body_orientation]);
    shieldSpriteSheetTexture.render(pos_x - camera.getX(), pos_y - camera.getY(), &shield_orientation_clips[e_body_orientation]);
}
