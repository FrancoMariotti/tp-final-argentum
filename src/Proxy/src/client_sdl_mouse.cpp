//
// Created by agustin on 26/6/20.
//

#include <SDL2/SDL_events.h>
#include <iostream>
#include "client_sdl_mouse.h"
#include "client_sdl_camera.h"
#include "common_blocking_queue.h"

SdlMouse::SdlMouse(SdlCamera& camera) :
    camera(camera),
    position{-1,-1},
    inventory_clicked_index(-1),
    clicked_in_map(false)
    {}

    /*Si el cliente hizo click se invalidan todos los atributos de posicion y si esta dentro de los limites
     * de la camara se guarda la nueva posicion del mapa en coordenadas del server*/
void SdlMouse::handleEvent(SDL_Event &event, bool &is_event_handled) {
    if ((event.type == SDL_MOUSEBUTTONDOWN) && !is_event_handled) {
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

void SdlMouse::use(BlockingQueue<std::unique_ptr<Message>> &clientEvents){
    if(position.x > -1 && position.y > -1){
          // clientEvents.push(std::unique_ptr <Message>(new Attack(username, position.x, position.y)))
        this->clear();
    }
}

/*Cada vez que el usuario hace un nuevo click se inicializan las entradas
 * position e index*/
void SdlMouse::clear(){
    position.x = -1;
    position.y = -1;
    inventory_clicked_index = -1;
    clicked_in_map = false;
}

SDL_Point SdlMouse::getPosition(){
    SDL_Point copy_position = position;
    //position.x = -1;
    //position.y = -1;
    return  copy_position;
}

bool SdlMouse::clickedInMap(){
    bool cpy = clicked_in_map;
    //clicked_in_map = false;
    return cpy;
}

/*Se invalidan los atributos de posicion y se setea el nuevo indice del inventario*/
void SdlMouse::setLastClickedItemIndex(const int i){
    this->clear();
    this->inventory_clicked_index = i;
}