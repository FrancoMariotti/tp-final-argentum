//
// Created by agustin on 22/6/20.
//

#include "client_sdl_camera.h"
#include "client_sdl_player.h"

#define MAP_WIDTH 15
#define MAP_HEIGHT 15

SdlCamera::SdlCamera(const int screen_width,const int screen_height, SdlPlayer& player) :
        CAMERA_WIDTH(screen_width),
        CAMERA_HEIGHT(screen_height),
        player(player) {
    camera_x = player.getPosX() /** + SdlPlayer::playerWidth / 2*/ - CAMERA_WIDTH / 2;
    camera_y = player.getPosY() - CAMERA_HEIGHT / 2;
}

SDL_Point SdlCamera::getCoordinates(const SDL_Point point) {
    return SDL_Point{(point.x * TILE_SIZE) - camera_x
            ,(point.y * TILE_SIZE) - camera_y};
}

void SdlCamera::move() {
    camera_x = player.getPosX() - (CAMERA_WIDTH / 2);
    camera_y = player.getPosY() - (CAMERA_HEIGHT / 2);
}

bool SdlCamera::isInCameraView(const SDL_Point& point) const {
    bool render = false;
    if(point.x * TILE_SIZE >= camera_x && point.x * TILE_SIZE <= camera_x + CAMERA_WIDTH
        && point.y * TILE_SIZE >= camera_y && point.y * TILE_SIZE <= camera_y + CAMERA_HEIGHT) {
        render = true;
    }
    return render;
}

bool SdlCamera::isInCameraView(const SDL_Point &point, int overload) const {
    bool is_inside = false;
    if(point.x  > camera_x && point.x  < camera_x + CAMERA_WIDTH
       && point.y > camera_y && point.y < camera_y + CAMERA_HEIGHT) {
        is_inside = true;
    }
    return is_inside;
}

int SdlCamera::getX(){
    return camera_x;
}

int SdlCamera::getY(){
    return camera_y;
}

int SdlCamera::toPixels(const int value) const{
    return value * TILE_SIZE;
}

SDL_Point SdlCamera::toServerCoordinates(const SDL_Point& point_in_pixels){
    return SDL_Point{(camera_x + point_in_pixels.x) / TILE_SIZE, (camera_y + point_in_pixels.y) / TILE_SIZE};
}
