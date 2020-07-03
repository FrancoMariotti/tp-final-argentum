//
// Created by agustin on 3/7/20.
//

#include <SDL2/SDL_timer.h>
#include "client_sdl_timer.h"

SdlTimer::SdlTimer() {
    this->start_ticks = 0;
    this->paused_ticks = 0;
    this->frames = 0;
    is_paused = false;
    is_started = false;
}

void SdlTimer::start() {
    is_started = true;
    is_paused = false;

    //Get the current clock time
    start_ticks = SDL_GetTicks();
    paused_ticks = 0;
}

/*Reinicializo todas las variables*/
void SdlTimer::stop() {
    is_started = false;
    is_paused = false;
    start_ticks = 0;
    paused_ticks = 0;
}

void SdlTimer::pause() {
    if (is_started && !is_paused){
        is_paused = true;
        //Calculate the paused ticks
        paused_ticks = SDL_GetTicks() - start_ticks;
        start_ticks = 0;
    }
}

void SdlTimer::unpause() {
    //If the timer is running and paused
    if(is_started && is_paused){
        is_paused = false;
        //Reset the starting ticks
        start_ticks = SDL_GetTicks() - paused_ticks;
        //Reset the paused ticks
        paused_ticks = 0;
    }
}

uint32_t SdlTimer::getTicks() {
    //The actual timer time
    uint32_t time = 0;
    if(is_started){
        if(is_paused){
            time = paused_ticks;
        } else {
            time = SDL_GetTicks() - start_ticks;
        }
    }
    return time;
}

void SdlTimer::incrementFrames(){
    frames++;
}

bool SdlTimer::isStarted() {
    return is_started;
}

bool SdlTimer::isPaused() {
    return is_started && is_paused;
}
