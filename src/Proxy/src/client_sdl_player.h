//
// Created by agustin on 8/6/20.
//

#ifndef SDLTEST_SDL_NPC_H
#define SDLTEST_SDL_NPC_H

#include <SDL2/SDL_image.h>
#include <vector>
#include "common_blocking_queue.h"


typedef struct t_movement{
    int x;
    int y;
}t_movement;

class SdlTexture;
class SdlPlayer {
private:
    enum e_head_orientation{
        FRONT_HEAD_SPRITE,
        RIGHT_HEAD_SPRITE,
        LEFT_HEAD_SPRITE,
        BACK_HEAD_SPRITE,
        TOTAL_HEAD_SPRITE
    };

    SdlTexture& m_body;
    SdlTexture& m_head_sprite_sheet_texture;
    //Dimensiones del npc
    int m_width;
    int m_height;
    //Maximum axis velocity of the dot
    const int m_vel = 10;
    //The X and Y offsets of the dot
    int m_pos_x, m_pos_y;
    //The velocity of the dot
    int m_vel_x, m_vel_y;

    SDL_Rect m_head_sprite_clips[TOTAL_HEAD_SPRITE];

    enum e_head_orientation m_face_orientation;

public:
    //Initializes the variables
    SdlPlayer(int x, int y, SdlTexture &texture, SdlTexture &head);

    //Ajusta la velocidad del npc
    void handleEvent(SDL_Event& e );

    //Mueve directamente al npc de manera axial
    void handleEvent(SDL_Event &e, BlockingQueue<t_movement> &proxySocket);

    //Mueve el npc
    void move(int screen_width, int screen_height);

    //Mueve el npc
    void move(t_movement move);

    //Muestra el npc en pantalla
    void render();
};


#endif //SDLTEST_SDL_NPC_H
