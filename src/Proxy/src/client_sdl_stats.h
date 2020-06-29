//
// Created by agustin on 26/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_STATS_H
#define ARGENTUM_CLIENT_SDL_STATS_H


#include "client_sdl_bar.h"
#include "client_sdl_output.h"
#include "common_message_structs.h"

class SdlStats {
private:
    SdlBar xpBar;
    SdlOutput level;
    SdlBar healthBar;
    SdlBar manaBar;
    SdlOutput gold;
    //Agrego esto para mostrar el texto "life" y "mana"
    SdlOutput manaLabel;
    SdlOutput lifeLabel;
public:
    SdlStats(int screen_width, int screen_height,const SdlWindow& window, TTF_Font *font);

    void update(t_stats stats);

    void render();
};


#endif //ARGENTUM_CLIENT_SDL_STATS_H
