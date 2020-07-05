//
// Created by agustin on 22/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_CAMERA_H
#define ARGENTUM_CLIENT_SDL_CAMERA_H


#include <SDL2/SDL_rect.h>

class SdlRenderablePlayable;
class SdlCamera {
private:
    const int CAMERA_WIDTH;
    const int CAMERA_HEIGHT;
    const SdlRenderablePlayable& player;
    int camera_x;
    int camera_y;

    const int TILE_SIZE = 32;

public:
    /*Inicializo la camara con las dimensiones de la pantalla*/
    SdlCamera(int screen_width, int screen_height, SdlRenderablePlayable& player);

    /*Devuelvo las coordenadas del @param point aplicando el offset de la camara*/
    SDL_Point getCoordinates(SDL_Point point);

    void move();

    bool isInCameraView(const SDL_Point& point) const;

    bool isInCameraView(const SDL_Point& point, int overload) const;

    int toPixels(int value) const;

    int getX() const;

    int getY() const;

    int getTileSize() const;

    SDL_Point toServerCoordinates(const SDL_Point &point_in_pixels);
};


#endif //ARGENTUM_CLIENT_SDL_CAMERA_H
