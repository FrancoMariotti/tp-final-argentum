//
// Created by agustin on 22/6/20.
//

#include "client_sdl_camera.h"
#include "client_sdl_window.h"

SdlCamera::SdlCamera(const std::string &username, const SdlWindow &window) :
        CAMERA_WIDTH(window.getWidth()),
        CAMERA_HEIGHT(window.getHeight()),
        following_id(username){
    camera_x =  /** + SdlPlayer::playerWidth / 2*/  CAMERA_WIDTH / 2;
    camera_y =   CAMERA_HEIGHT / 2;
}

SDL_Point SdlCamera::getCoordinates(const SDL_Point point) const {
    return SDL_Point{(point.x * TILE_SIZE) - camera_x
            ,(point.y * TILE_SIZE) - camera_y};
}

void SdlCamera::move(const SDL_Point player_pos) {
    //camera_x = player_pos.x - (CAMERA_WIDTH / 2);
    //camera_y = player_pos.y - (CAMERA_HEIGHT / 2);
    camera_x = player_pos.x - (CAMERA_WIDTH / 2) + CAMERA_WIDTH * 0.135;
    camera_y = player_pos.y - (CAMERA_HEIGHT / 2) - CAMERA_HEIGHT * 0.06;
    /*if(camera_x < 0){
        camera_x = 0;
    }
    if(camera_y < 0){
        camera_y = 0;
    }*/
}

bool SdlCamera::isInCameraView(const SDL_Point& point) const {
    bool render = false;
    //Le resto TILE_SIZE a la camara para que renderize los tiles que estan justo en el borde para evitar bordes blancos.
    if(point.x * TILE_SIZE >= camera_x - TILE_SIZE && point.x * TILE_SIZE <= camera_x + CAMERA_WIDTH
        && point.y * TILE_SIZE >= camera_y - TILE_SIZE && point.y * TILE_SIZE <= camera_y + CAMERA_HEIGHT) {
        render = true;
    }
    return render;
}

bool SdlCamera::isInCameraView(const SDL_Point &point, int overload) const {
    return (point.x  > 0 && point.x < CAMERA_WIDTH && point.y > 0 && point.y < CAMERA_HEIGHT);
}

int SdlCamera::getX() const{
    return camera_x;
}

int SdlCamera::getY() const{
    return camera_y;
}

int SdlCamera::toPixels(const int value) const{
    return value * TILE_SIZE;
}

SDL_Point SdlCamera::toServerCoordinates(const SDL_Point& point_in_pixels) const{
    return SDL_Point{(camera_x + point_in_pixels.x) / TILE_SIZE, (camera_y + point_in_pixels.y) / TILE_SIZE};
}

SDL_Point SdlCamera::posToServerCoordinates(const SDL_Point& point_in_pixels) const{
    return SDL_Point{point_in_pixels.x / TILE_SIZE, point_in_pixels.y / TILE_SIZE};
}


int SdlCamera::getTileSize() const {
    return TILE_SIZE;
}
