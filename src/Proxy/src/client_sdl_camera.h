//
// Created by agustin on 22/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_CAMERA_H
#define ARGENTUM_CLIENT_SDL_CAMERA_H


#include <SDL2/SDL_rect.h>

class SdlPlayer;
class SdlCamera {
private:
    const int camera_width;
    const int camera_height;
    const SdlPlayer& player;
    int camera_x;
    int camera_y;

public:
    /*Inicializo la camara con las dimensiones de la pantalla*/
    SdlCamera(int screen_width, int screen_height, SdlPlayer& player);

    /*Devuelvo las coordenadas del @param point aplicando el offset de la camara*/
    SDL_Point getCoordinates(SDL_Point point);

    void move();

    bool isInCameraView(const SDL_Point& point) const;
};


#endif //ARGENTUM_CLIENT_SDL_CAMERA_H
