//
// Created by agustin on 22/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_CAMERA_H
#define ARGENTUM_CLIENT_SDL_CAMERA_H


#include <SDL2/SDL_rect.h>
#include <string>

class SdlRenderablePlayable;
class SdlCamera {
private:
    const int CAMERA_WIDTH;
    const int CAMERA_HEIGHT;
    int camera_x;
    int camera_y;

    /*el id del renderizable al cual sigue la camara,
     * en este caso el personaje del cliente*/
    const std::string& following_id;
    const int TILE_SIZE = 32;

public:
    /*Inicializo la camara con las dimensiones de la pantalla*/
    SdlCamera(const int screen_width, const int screen_height, const std::string &username);

    /*Seteo el id de lo que la camara esta siguiendo*/
    //void setIdToFollow(const std::string& renderable_id);

    /*Devuelvo las coordenadas del @param point aplicando el offset de la camara*/
    SDL_Point getCoordinates(SDL_Point point) const;

    void move(const SDL_Point player_pos);

    bool isInCameraView(const SDL_Point& point) const;

    bool isInCameraView(const SDL_Point& point, int overload) const;

    int toPixels(int value) const;

    int getX() const;

    int getY() const;

    int getTileSize() const;

    SDL_Point toServerCoordinates(const SDL_Point &point_in_pixels) const;

    SDL_Point posToServerCoordinates(const SDL_Point &point_in_pixels) const;
};


#endif //ARGENTUM_CLIENT_SDL_CAMERA_H
