//
// Created by agustin on 21/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_WORLD_H
#define ARGENTUM_CLIENT_SDL_WORLD_H

#include <SDL2/SDL_rect.h>
#include <map>
#include "client_sdl_texture.h"
#include "client_sdl_camera.h"


class SdlWindow;
class SdlTexture;
class SdlWorld {
private:
    SdlTexture worldSpriteSheetTexture;
    std::map<int, SDL_Rect> world_tiles_clips;
    std::map<int, std::vector<SDL_Point>> world_tiles;

    const int TILE_SIZE = 32;

    /**Al init debemos pasarle el mensaje con las dimensiones del mapa*/
    //const int WORLD_TILES_WIDTH;
    //const int WORLD_TILES_HEIGHT;
public:
    /* Cargo la textura con todos los tiles del mundo
     * Cargo el map con los recortes de cada tile que se van a utilizar para dibujar el mundo*/
    explicit SdlWorld(const SdlWindow& window);

    void render(const int x, const int y, const int tile_id);

    void add(const int x, const int y, const int tile_id);

    void render(SdlCamera &camera);

};


#endif //ARGENTUM_CLIENT_SDL_WORLD_H
