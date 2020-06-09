//
// Created by agustin on 8/6/20.
//

#ifndef SDLTEST_SDL_NPC_H
#define SDLTEST_SDL_NPC_H

#include <SDL2/SDL_image.h>
#include <vector>

#define HEAD_SPRITES 4

class SdlTexture;

class SdlNPC {
private:
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

    SDL_Rect head_sprite_clips[HEAD_SPRITES];

public:
    //Initializes the variables
    SdlNPC(int x, int y, SdlTexture &texture, SdlTexture &head);

    //Ajusta la velocidad del npc
    void handleEvent(SDL_Event& e );

    //Mueve directamente al npc de manera axial, no diagonal
    void handleEvent(SDL_Event &e, int overload);

    //Mueve el npc
    void move(int screen_width, int screen_height);

    //Muestra el npc en pantalla
    void render();
};


#endif //SDLTEST_SDL_NPC_H
