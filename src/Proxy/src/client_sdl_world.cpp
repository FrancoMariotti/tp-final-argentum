//
// Created by agustin on 21/6/20.
//

#include <vector>
#include <iostream>
#include "client_sdl_world.h"
#include "client_sdl_camera.h"

#define IMAGE_TILE_SIZE 32

SdlWorld::SdlWorld(const SdlWindow& window) :
        worldSpriteSheetTexture(IMAGE_TILE_SIZE, IMAGE_TILE_SIZE, "../../Proxy/assets/wood-floor-sprite-png.png", window) {

    const int tile = IMAGE_TILE_SIZE;
    /**Tiled
     * Pasto: 233
     * hongo: 480
     * piedra 420
     * lava: */
    /* Hacer una lista de IDs a utilizar y que luego por cada id hago un emplace calculando su x e y mod y / del ID */
    /*this->world_tiles_clips.emplace(std::make_pair(233, SDL_Rect{IMAGE_TILE_SIZE,11*tile,IMAGE_TILE_SIZE,IMAGE_TILE_SIZE}));
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
    */

    for (int i = 0; i <= 483 ; ++i) {
        int fil = i / 21;
        int col = (i % 21);
        if(col != 0){
            col--;
        } else {
            fil = i / 22;
            col = i / 21;
        }
        this->world_tiles_clips.emplace(std::make_pair(i, SDL_Rect{col*tile,fil*tile,tile,tile}));
    }
}

void SdlWorld::addFloorTile(const int x, const int y, const int tile_id){
    world_floor_tiles[tile_id].emplace_back(SDL_Point{x, y});
}

void SdlWorld::addObstacleTile(const int x, const int y, const int tile_id){
    world_obstacles_tiles[tile_id].emplace_back(SDL_Point{x, y});
}

void SdlWorld::renderFloor(SdlCamera &camera) {
    std::map<int, std::vector<SDL_Point>>::iterator iterator = world_floor_tiles.begin();
    while(iterator != world_floor_tiles.end()){
        for(auto value_iterator = iterator->second.begin();
        value_iterator != iterator->second.end() ; ++value_iterator) {
            if(camera.isInCameraView(*value_iterator)){
                SDL_Point relative_point = camera.getCoordinates(*value_iterator);
                worldSpriteSheetTexture.render(relative_point.x,
                                               relative_point.y,
                                               &world_tiles_clips.at(iterator->first));
            }
        }
        iterator++;
    }
}

void SdlWorld::renderObstacles(SdlCamera &camera) {
    std::map<int, std::vector<SDL_Point>>::iterator iterator = world_obstacles_tiles.begin();
    while(iterator != world_obstacles_tiles.end()){
        for(auto value_iterator = iterator->second.begin();
        value_iterator != iterator->second.end() ; ++value_iterator) {
            if(camera.isInCameraView(*value_iterator)){
                SDL_Point relative_point = camera.getCoordinates(*value_iterator);
                worldSpriteSheetTexture.render(relative_point.x,
                                               relative_point.y,
                                               &world_tiles_clips.at(iterator->first));
            }
        }
        iterator++;
    }
}