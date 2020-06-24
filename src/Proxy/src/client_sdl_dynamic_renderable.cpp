//
// Created by agustin on 24/6/20.
//

#include "client_sdl_dynamic_renderable.h"
#include "client_sdl_camera.h"

SdlDynamicRenderable::SdlDynamicRenderable(const int x, const  int y,
        const int width, const int height, const std::string& id, const SdlWindow &window) :
    bodySpriteSheetTexture(width, height,"../../Proxy/assets/" + id + ".png", window),
    pos_x(x),
    pos_y(y),
    orientation_clips{{0,0,0,0},{0,0,0,0},
                      {0,0,0,0},{0,0,0,0}},
    e_current_orientation(FRONT) {

    /**Deber ia hacer un map que tenga un id y orientation_clips[4] asi resuelvo tod por id*/
    for (int i = 0; i < TOTAL_ORIENTATIONS ; ++i) {
        orientation_clips[i] = {0, i*height, width, height};
    }
}

void SdlDynamicRenderable::update(const int vel_x, const int vel_y){
    pos_x += vel_x;
    pos_y -= vel_y;
    if(vel_x > 0){
        e_current_orientation = RIGHT;
    } else if(vel_x < 0){
        e_current_orientation = LEFT;
    } else if(vel_y > 0){
        e_current_orientation = FRONT;
    } else if(vel_y < 0){
        e_current_orientation = BACK;
    }
}

void SdlDynamicRenderable::render(SdlCamera& camera){
    bodySpriteSheetTexture.render(pos_x - camera.getX(), pos_y - camera.getY(), &orientation_clips[e_current_orientation]);
}