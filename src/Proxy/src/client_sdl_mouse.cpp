//
// Created by agustin on 26/6/20.
//

#include <SDL2/SDL_events.h>
#include <iostream>
#include "client_sdl_mouse.h"
#include "client_sdl_camera.h"

SdlMouse::SdlMouse(SdlCamera& camera) :
    clicked_in_map(false),
    camera(camera)
    {}

void SdlMouse::handleEvent(SDL_Event &event, bool &is_event_handled) {
    if ((event.type == SDL_MOUSEBUTTONDOWN) && !is_event_handled) {
        int x,y;
        /*Devuelve la posicion del mouse*/
        SDL_GetMouseState(&x,&y);
        SDL_Point mouse_click{x,y};
        if(camera.isInCameraView(mouse_click,0)){
            /*click dentro de la camara*/
            this->position = camera.toServerCoordinates(mouse_click);
            std::cout <<"click_x: " << position.x << "click_y: " << position.y << std::endl;
            clicked_in_map = true;
        }
    }
}

int SdlMouse::getX(){
    return position.x;
}

int SdlMouse::getY(){
    return position.y;
}