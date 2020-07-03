//
// Created by agustin on 3/7/20.
//

#ifndef ARGENTUM_CLIENT_SDL_TIMER_H
#define ARGENTUM_CLIENT_SDL_TIMER_H


#include <stdint-gcc.h>

class SdlTimer{
private:
    uint32_t start_ticks;
    uint32_t paused_ticks;
    unsigned int frames;
    bool is_paused;
    bool is_started;

public:
    SdlTimer();
    /*Empieza a contar*/
    void start();
    /*Detiene y reinicializa*/
    void stop();
    /*Pausa y empieza a contar tiempo pausado*/
    void pause();
    /*Despausa y sigue contando en donde se quedo*/
    void unpause();
    /*Devuelve la cantidad de ticks desde que empezo a contar
    * o si esta en pausa, el tiempo que lleva en pausa*/
    uint32_t getTicks();
    bool isStarted();
    bool isPaused();

    void incrementFrames();
};




#endif //ARGENTUM_CLIENT_SDL_TIMER_H
