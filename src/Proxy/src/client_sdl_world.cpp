//
// Created by agustin on 21/6/20.
//

#include <vector>
#include <iostream>
#include "client_sdl_world.h"
#include "client_sdl_camera.h"


SdlWorld::SdlWorld(const SdlWindow& window) :
        worldSpriteSheetTexture(32, 32, "../../Proxy/assets/wood-floor-sprite-png.png", window) {
    /**Tiled
     * Pasto: 233*/
    this->world_tiles_clips.emplace(std::make_pair(233, SDL_Rect{32,352,32,32}));
    //this->world_tiles_clips.emplace(std::make_pair("hongo", SDL_Rect{17*32,22*32,32,32}));
    //this->world_tiles_clips.emplace(std::make_pair("roca", SDL_Rect{20*32,19*32,32,32}));

}

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

