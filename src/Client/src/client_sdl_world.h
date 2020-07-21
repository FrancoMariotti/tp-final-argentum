//
// Created by agustin on 21/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_WORLD_H
#define ARGENTUM_CLIENT_SDL_WORLD_H

#include <SDL2/SDL_rect.h>
#include <map>
#include "client_sdl_texture.h"
#include "client_sdl_camera.h"
#include "client_sdl_inventory.h"


class SdlWindow;
class SdlTexture;
class SdlWorld {
private:
    SdlTexture worldSpriteSheetTexture;
    std::map<int, SDL_Rect> world_tiles_clips;
    std::map<int, std::vector<SDL_Point>> world_floor_tiles;
    std::map<int, std::vector<SDL_Point>> world_obstacles_tiles;
    /*Mapea por id de item y posicion en la que se encuentra*/
    std::map<std::string, std::vector<SDL_Point>> world_drops;
    int map_width;
    int map_height;

public:
    /* Cargo la textura con todos los tiles del mundo
     * Cargo el map con los recortes de cada tile que se van a utilizar para dibujar el mundo*/
    explicit SdlWorld(const SdlWindow& window);
    void setDimensions(int w, int h);
    /*Agrega los ID de cada tile en @param data al map del suelo o de los obstaculos dependiendeo del valor de @param init*/
    void addLayer(std::vector<int> data, const int init);
    void addFloorTile(int x, int y, int tile_id);
    void addObstacleTile(int x, int y, int tile_id);
    /*Vacia el mapa de drops y agrega los drops de la lista @param drops*/
    void updateDrops(const std::vector<location_t> &drops);
    /*Renderiza aquellos drops que se encuentra dentro de la vista de la camera*/
    void renderDrops(SdlInventory &inventory, const SdlCamera &camera);
    /*Renderiza el layer del piso y el de obstaculos*/
    void render(SdlCamera &camera);

private:

    void render(SdlCamera &camera, std::map<int, std::vector<SDL_Point>> &layer);
    SDL_Rect & getClip(const int id);
};


#endif //ARGENTUM_CLIENT_SDL_WORLD_H
