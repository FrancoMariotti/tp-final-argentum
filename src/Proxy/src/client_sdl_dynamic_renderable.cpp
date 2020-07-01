//
// Created by agustin on 24/6/20.
//

#include "client_sdl_dynamic_renderable.h"
#include "client_sdl_camera.h"
#include "client_sdl_texture.h"

SdlDynamicRenderable::SdlDynamicRenderable(const int x, const int y, SdlTexture &bodyTexture) :
    pos_x(x),
    pos_y(y),
    orientation_clips{{0,0,0,0},{0,0,0,0},
                      {0,0,0,0},{0,0,0,0}},
    e_current_orientation(FRONT),
    bodySpriteSheetTexture(bodyTexture){
    /**Deber ia hacer un map que tenga un id y orientation_clips[4] asi resuelvo tod por id*/
    for (int i = 0; i < TOTAL_ORIENTATIONS ; ++i) {
        orientation_clips[i] = {0, i*bodyTexture.getHeight(), bodyTexture.getWidth(), bodyTexture.getHeight()};
    }
}

void SdlDynamicRenderable::update(const int new_x, const int new_y, SdlCamera &camera) {
    int old_x = pos_x;
    int old_y = pos_y;
    pos_x = camera.toPixels(new_x);
    pos_y = camera.toPixels(new_y);
    if(pos_x > old_x){
        e_current_orientation = RIGHT;
    } else if(pos_x < old_x){
        e_current_orientation = LEFT;
    } else if(pos_y > old_y){
        e_current_orientation = FRONT;
    } else if(pos_y < old_y){
        e_current_orientation = BACK;
    }
}

void SdlDynamicRenderable::render(SdlCamera& camera){
    bodySpriteSheetTexture.render(pos_x - camera.getX(), pos_y - camera.getY(), &orientation_clips[e_current_orientation]);
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

void SdlPlayableCharacter::render(SdlCamera& camera){
    SdlDynamicRenderable::render(camera);
    headSpriteSheetTexture.render(pos_x - camera.getX(), pos_y - camera.getY(), &head_orientation_clips[e_current_orientation]);
    helmetSpriteSheetTexture.render(pos_x - camera.getX(), pos_y - camera.getY(), &head_orientation_clips[e_current_orientation]);
    weaponSpriteSheetTexture.render(pos_x - camera.getX(), pos_y - camera.getY(), &weapon_orientation_clips[e_current_orientation]);
    shieldSpriteSheetTexture.render(pos_x - camera.getX(), pos_y - camera.getY(), &shield_orientation_clips[e_current_orientation]);
}