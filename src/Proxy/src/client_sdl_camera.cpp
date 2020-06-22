//
// Created by agustin on 22/6/20.
//

#include "client_sdl_camera.h"
#include "client_sdl_player.h"

SdlCamera::SdlCamera(const int screen_width,const int screen_height, SdlPlayer& player) :
    camera_width(screen_width),
    camera_height(screen_height),
    player(player) {
    camera_x = player.getPosX() /** + SdlPlayer::playerWidth / 2*/ - camera_width / 2;
    camera_y = player.getPosY() - camera_height / 2;
}

SDL_Point SdlCamera::getCoordinates(const SDL_Point point) {
    return SDL_Point{point.x * 32 + camera_x
            ,point.y *32 + camera_y};
}

void SdlCamera::move() {
    camera_x = player.getPosX() - camera_width / 2;
    camera_y = player.getPosY() - camera_height / 2;
}

bool SdlCamera::isInCameraView(const SDL_Point& point) const {
    bool render = false;
    if(point.x * 32 > camera_x && point.x * 32 < camera_x + camera_width
        && point.y * 32 > camera_y && point.y * 32 < camera_y + camera_height) {
        render = true;
    }
    return render;
}
