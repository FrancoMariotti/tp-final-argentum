//
// Created by agustin on 26/6/20.
//

#include <SDL2/SDL_events.h>
#include <iostream>
#include "client_sdl_mouse.h"
#include "client_sdl_camera.h"
#include "Common/BlockingQueue.h"

SdlMouse::SdlMouse(SdlCamera& camera) :
    camera(camera),
    position{-1,-1},
    inventory_clicked_index(0),
    left_click(0),
    right_click(0),
    clicked_in_map(false)
    {}

    /*Si el cliente hizo click se invalidan todos los atributos de posicion y si esta dentro de los limites
     * de la camara se guarda la nueva posicion del mapa en coordenadas del server*/
void SdlMouse::handleEvent(SDL_Event &event, bool &is_event_handled) {
    if ((event.type == SDL_MOUSEBUTTONDOWN) && !is_event_handled) {
        if (event.button.button == SDL_BUTTON_RIGHT){
            right_click++;
        } else if (event.button.button == SDL_BUTTON_LEFT){
            this->left_click++;
        }
        this->clear();
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

void SdlMouse::use() {
    if(position.x > -1 && position.y > -1 && right_click > 0){
        std::cout << "DEBUG: attack" << std::endl;
        this->mediator->notify(this, position);
        right_click--;
        this->clear();
    } else if (left_click > 0) {
        mediator->notify(this, position, 0);
        left_click--;
    }
}

/*Cada vez que el usuario hace un nuevo click se inicializan las entradas
 * position e index*/
void SdlMouse::clear(){
    position.x = -1;
    position.y = -1;
    inventory_clicked_index = 0;
    clicked_in_map = false;
    mediator->notify(this);
}
