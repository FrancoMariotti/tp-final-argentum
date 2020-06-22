//
// Created by agustin on 21/6/20.
//

#include <vector>
#include <iostream>
#include "client_sdl_world.h"


SdlWorld::SdlWorld(const SdlWindow& window) :
        worldSpriteSheetTexture(32, 32, "../../Proxy/assets/wood-floor-sprite-png.png", window) {
    /**Test*/
    std::vector<std::string> tile_names{"flores", "pantano"};
    for (unsigned long i = 0;  i < tile_names.size() ; ++i) {
        this->world_tiles_clips.emplace(std::make_pair(tile_names[i], SDL_Rect{(int) (i+1)*3*32,352,32,32}));
    }
    /***/

    this->world_tiles_clips.emplace(std::make_pair("pasto", SDL_Rect{32,352,32,32}));
    this->world_tiles_clips.emplace(std::make_pair("hongo", SDL_Rect{17*32,22*32,32,32}));
    this->world_tiles_clips.emplace(std::make_pair("roca", SDL_Rect{20*32,19*32,32,32}));

}

void SdlWorld::add(const int x, const int y, const std::string &id){
    world_tiles[id].emplace_back(SDL_Point{x,y});
}

void SdlWorld::render(const int x, const int y, const std::string &id){
    worldSpriteSheetTexture.render(x, y, &world_tiles_clips.at(id));
}


void SdlWorld::render(){
    std::map<std::string, std::vector<SDL_Point>>::iterator iterator = world_tiles.begin();
    while(iterator != world_tiles.end()){
        for(auto value_iterator = iterator->second.begin() ;
        value_iterator != iterator->second.end() ; ++value_iterator) {
            worldSpriteSheetTexture.render(value_iterator->x * TILE_SIZE,
                    value_iterator->y * TILE_SIZE,
                    &world_tiles_clips.at(iterator->first));
        }
        iterator++;
    }
}