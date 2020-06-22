//
// Created by agustin on 21/6/20.
//

#include <vector>
#include "client_sdl_world.h"


SdlWorld::SdlWorld(const SdlWindow& window) :
        worldSpriteSheetTexture(32, 32, "../../Proxy/assets/wood-floor-sprite-png.png", window) {



    std::vector<std::string> tile_names{"flores", "pantano"};
    for (unsigned long i = 0;  i < tile_names.size() ; ++i) {
        this->world_tiles_clips.emplace(std::make_pair(tile_names[i], SDL_Rect{(int) i*3*32,352,32,32}));
    }
    this->world_tiles_clips.emplace(std::make_pair("pasto", SDL_Rect{32,352,32,32}));
    this->world_tiles_clips.emplace(std::make_pair("hongo", SDL_Rect{17*32,22*32,32,32}));
    this->world_tiles_clips.emplace(std::make_pair("roca", SDL_Rect{20*32,19*32,32,32}));

}

void SdlWorld::render(const int x, const int y, const std::string &id){
    worldSpriteSheetTexture.render(x, y, &world_tiles_clips.at(id));
}