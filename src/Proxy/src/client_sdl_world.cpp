//
// Created by agustin on 21/6/20.
//

#include "client_sdl_world.h"


SdlWorld::SdlWorld(const SdlWindow& window) :
    worldSpriteSheet(32,32,"../../Proxy/assets/wood-floor-sprite-png.png", window) {

        for (int i = 0; i < 4 ; ++i) {
            this->world_tiles_clips.emplace(std::make_pair(i, SDL_Rect{i*3*32,352,32,32}));
        }

}

void SdlWorld::render(){
    worldSpriteSheet.render(200,200,&world_tiles_clips.at(0));
}


void SdlWorld::render(const int x, const int y,const int id){
    worldSpriteSheet.render(x, y, &world_tiles_clips.at(id));
}