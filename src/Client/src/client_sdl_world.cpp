//
// Created by agustin on 21/6/20.
//

#include <vector>
#include <iostream>
#include <Common/OsException.h>
#include "client_sdl_world.h"
#include "client_sdl_camera.h"
#include "client_sdl_inventory.h"

#define IMAGE_TILE_SIZE 32
#define TILES 483

SdlWorld::SdlWorld(const SdlWindow& window) :
        worldSpriteSheetTexture(IMAGE_TILE_SIZE, IMAGE_TILE_SIZE,
                "../../Client/assets/wood-floor-sprite-png.png", window),
                map_width(0),
                map_height(0){

    const int tile = IMAGE_TILE_SIZE;

    for (int i = 0; i <= TILES ; ++i) {
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


void SdlWorld::addLayer(std::vector<int> data, const int init){
    for (int i = 0; i < (int) data.size() ; ++i) {
        if (data[i]!= 0) {
            int x = i % this->map_width;
            int y = i / this->map_height;
            if (init == 1) {
                addFloorTile(x, y, data[i]);
            } else {
                addObstacleTile(x, y, data[i]);
            }
        }
    }
}

void SdlWorld::addFloorTile(const int x, const int y, const int tile_id){
    world_floor_tiles[tile_id].emplace_back(SDL_Point{x, y});
}

void SdlWorld::addObstacleTile(const int x, const int y, const int tile_id){
    world_obstacles_tiles[tile_id].emplace_back(SDL_Point{x, y});
}

void SdlWorld::render(SdlCamera& camera){
    this->render(camera, this->world_floor_tiles);
    this->render(camera, this->world_obstacles_tiles);
}

SDL_Rect & SdlWorld::getClip(const int id){
    auto search = world_tiles_clips.find(id);
    if(search == world_tiles_clips.end()){
        throw OSError("<SdlWorld::getClip> "
                      "el id del tile es invalido. @param: %d", id);
    }
    return search->second;
}

void SdlWorld::render(SdlCamera& camera, std::map<int, std::vector<SDL_Point>>& layer){
    std::map<int, std::vector<SDL_Point>>::iterator iterator = layer.begin();
    while(iterator != layer.end()){
        for(auto value_iterator = iterator->second.begin();
            value_iterator != iterator->second.end() ; ++value_iterator) {
            if(camera.isInCameraView(*value_iterator)){
                SDL_Point relative_point = camera.getCoordinates(*value_iterator);
                worldSpriteSheetTexture.render(relative_point.x,
                                               relative_point.y,
                                               &getClip(iterator->first));
            }
        }
        iterator++;
    }
}

void SdlWorld::setDimensions(int w, int h) {
    this->map_width = w;
    this->map_height = h;
}

/*Re-usamos el spawn_character_t para los items*/
void SdlWorld::updateDrops(const std::vector<location_t> &drops) {
    for(auto & world_drop : world_drops){
        world_drop.second.clear();
    }
    for(auto it = drops.begin(); it != drops.end(); it++ ){
        int x = it->x;
        int y = it->y;
        world_drops[it->id].emplace_back(SDL_Point{x, y});
    }

}

void SdlWorld::renderDrops(SdlInventory &inventory, const SdlCamera &camera) {
    auto it = world_drops.begin();
    for(; it != world_drops.end(); it++){
        auto value_it = it->second.begin();
        for(; value_it != it->second.end(); value_it++){
            if(camera.isInCameraView(*value_it)){
                SDL_Point relativeDropPosition = camera.getCoordinates(*value_it);
                inventory.renderDrop(relativeDropPosition.x, relativeDropPosition.y, it->first);
            }
        }
    }
}