//
// Created by agustin on 30/6/20.
//

#include <SDL2/SDL_events.h>
#include "client_sdl_keyboard.h"

SdlKeyboard::SdlKeyboard() :
    player_vel_x(0),
    player_vel_y(0),
    handle_events(true),
    game_loops_counter(0)
    {}

void SdlKeyboard::handleEvent(SDL_Event &e, bool &is_event_handled) {

    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch(e.key.keysym.sym){
            case SDLK_UP: player_vel_y = -VEL;
                break;
            case SDLK_DOWN: player_vel_y = +VEL;
                break;
            case SDLK_LEFT: player_vel_x = -VEL;
                break;
            case SDLK_RIGHT: player_vel_x = +VEL;
                break;

        }
    }
/*
    if(e.type == SDL_KEYUP && e.key.repeat == 0){
        switch(e.key.keysym.sym){
            case SDLK_UP: player_vel_y += VEL;
            break;
            case SDLK_DOWN: player_vel_y -= VEL;
            break;
            case SDLK_LEFT: player_vel_x += VEL;
            break;
            case SDLK_RIGHT: player_vel_x -= VEL;
            break;
        }
    }

    if(!handle_events){
        game_loops_counter--;
        if(game_loops_counter <= 0){
            handle_events = true;
            player_vel_x = 0;
            player_vel_y = 0;
        }
    }
*/
}

void SdlKeyboard::movePlayer(BlockingQueue<std::unique_ptr<Message>> &clientEvents) {
    if((player_vel_x != 0 || player_vel_y != 0) && handle_events){
        mediator->notify(this, player_vel_x, player_vel_y);
        player_vel_x = 0;
        player_vel_y = 0;
    }
}

void SdlKeyboard::setEventHandling(bool handle,const int game_loops){
    this->handle_events = handle;
    this->game_loops_counter = game_loops;
}