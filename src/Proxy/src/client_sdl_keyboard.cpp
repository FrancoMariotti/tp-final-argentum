//
// Created by agustin on 30/6/20.
//

#include <SDL2/SDL_events.h>
#include "client_sdl_keyboard.h"

SdlKeyboard::SdlKeyboard() :
    player_vel_x(0),
    player_vel_y(0)
    {}

void SdlKeyboard::handleEvent(SDL_Event &e, bool &is_event_handled) {
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        switch(e.key.keysym.sym){
            case SDLK_UP: player_vel_y -= VEL;
                break;
            case SDLK_DOWN: player_vel_y += VEL;
                break;
            case SDLK_LEFT: player_vel_x -= VEL;
                break;
            case SDLK_RIGHT: player_vel_x += VEL;
                break;

        }
    }
}

void SdlKeyboard::movePlayer(BlockingQueue<std::unique_ptr<Message>> &clientEvents) {
    if(player_vel_x != 0 || player_vel_y != 0){
        mediator->notify(this, player_vel_x, player_vel_y);
        player_vel_x = 0;
        player_vel_y = 0;
    }
}
