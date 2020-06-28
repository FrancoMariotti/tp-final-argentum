//
// Created by agustin on 26/6/20.
//

#include <SDL2/SDL_events.h>
#include <iostream>
#include "client_sdl_mouse.h"
#include "client_sdl_camera.h"

SdlMouse::SdlMouse(SdlCamera& camera) :
    camera(camera),
    position{-1,-1},
    clicked_in_map(false)
    {}

void SdlMouse::handleEvent(SDL_Event &event, bool &is_event_handled) {
    if ((event.type == SDL_MOUSEBUTTONDOWN) && !is_event_handled) {
        int x,y;
        /*Devuelve la posicion del mouse*/
        SDL_GetMouseState(&x,&y);
        SDL_Point mouse_click{x,y};
        if(camera.isInCameraView(mouse_click,0)){
            /*click dentro de la camara*/
            clicked_in_map = true;
            this->position = camera.toServerCoordinates(mouse_click);
            std::cout <<"click_x: " << position.x << "click_y: " << position.y << std::endl;
        }
    }
}

SDL_Point SdlMouse::getPosition(){
    SDL_Point copy_position = position;
    position.x = -1;
    position.y = -1;
    return  copy_position;
}

bool SdlMouse::clickedInMap(){
    bool cpy = clicked_in_map;
    clicked_in_map = false;
    return cpy;
}