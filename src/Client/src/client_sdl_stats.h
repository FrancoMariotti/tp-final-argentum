//
// Created by agustin on 26/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_STATS_H
#define ARGENTUM_CLIENT_SDL_STATS_H


#include "client_sdl_bar.h"
#include "client_sdl_output.h"
#include "Common/Messages/message_structs.h"

class SdlStats {
private:
    const int UPPER;
    const int LOWER;

    SdlLabel levelLabel;
    SdlBar xpBar;
    SdlBar manaBar;
    SdlBar healthBar;
    SdlLabel goldLabel;
    SdlLabel manaLabel;
    SdlLabel lifeLabel;
public:
    SdlStats(const SdlWindow &window, TTF_Font *font);

    /*Actualiza los stats del jugador con los nuevos datos de @param stats*/
    void update(t_stats stats);

    void render();
};


#endif //ARGENTUM_CLIENT_SDL_STATS_H
