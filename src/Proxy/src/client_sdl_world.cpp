//
// Created by agustin on 21/6/20.
//

#include <vector>
#include "client_sdl_world.h"
#include "client_sdl_camera.h"

#define IMAGE_TILE_SIZE 32

SdlWorld::SdlWorld(const SdlWindow& window) :
        worldSpriteSheetTexture(IMAGE_TILE_SIZE, IMAGE_TILE_SIZE, "../../Proxy/assets/wood-floor-sprite-png.png", window) {
    /**Tiled
     * Pasto: 233
     * hongo: 480
     * piedra 420
     * lava: */
    /* Hacer una lista de IDs a utilizar y que luego por cada id hago un emplace calculando su x e y mod y / del ID */
    this->world_tiles_clips.emplace(std::make_pair(233, SDL_Rect{IMAGE_TILE_SIZE,352,IMAGE_TILE_SIZE,IMAGE_TILE_SIZE}));
    this->world_tiles_clips.emplace(std::make_pair(480, SDL_Rect{17*32,22*32,32,32}));
    this->world_tiles_clips.emplace(std::make_pair(420, SDL_Rect{20*32,19*32,32,32}));
    this->world_tiles_clips.emplace(std::make_pair(304, SDL_Rect{9*32,14*32,32,32}));
    this->world_tiles_clips.emplace(std::make_pair(305, SDL_Rect{10*32,14*32,32,32}));
    this->world_tiles_clips.emplace(std::make_pair(306, SDL_Rect{11*32,14*32,32,32}));
    this->world_tiles_clips.emplace(std::make_pair(325, SDL_Rect{9*32,15*32,32,32}));
    this->world_tiles_clips.emplace(std::make_pair(326, SDL_Rect{10*32,15*32,32,32}));
    this->world_tiles_clips.emplace(std::make_pair(327, SDL_Rect{11*32,15*32,32,32}));
    this->world_tiles_clips.emplace(std::make_pair(346, SDL_Rect{9*32,16*32,32,32}));
    this->world_tiles_clips.emplace(std::make_pair(347, SDL_Rect{10*32,16*32,32,32}));
    this->world_tiles_clips.emplace(std::make_pair(348, SDL_Rect{11*32,16*32,32,32}));

}

/**El orden en que se agregan los tiles es el orden en el que se muestran, ojo con que se pisen*/
void SdlWorld::add(const int x, const int y, const int tile_id){
    world_tiles[tile_id].emplace_back(SDL_Point{x, y});
}

void SdlWorld::render(const int x, const int y, const int tile_id){
    worldSpriteSheetTexture.render(x, y, &world_tiles_clips.at(tile_id));
}


void SdlWorld::render(SdlCamera &camera) {
    std::map<int, std::vector<SDL_Point>>::iterator iterator = world_tiles.begin();
    while(iterator != world_tiles.end()){
        for(auto value_iterator = iterator->second.begin();
        value_iterator != iterator->second.end() ; ++value_iterator) {
            SDL_Point relative_point = camera.getCoordinates(*value_iterator);
            worldSpriteSheetTexture.render(relative_point.x,
                    relative_point.y,
                    &world_tiles_clips.at(iterator->first));
        }
        iterator++;
    }
}

