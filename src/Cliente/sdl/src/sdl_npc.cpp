//
// Created by agustin on 8/6/20.
//

#include "sdl_npc.h"
#include "sdl_texture.h"

#define HUMANOID_HEAD_WIDTH 17
#define HUMANOID_HEAD_HEIGHT 20

SdlNPC::SdlNPC(int x, int y, SdlTexture &texture, SdlTexture &head) :
        m_body(texture),
        m_head_sprite_sheet_texture(head){
    //Initialize the offsets
    m_pos_x = x;
    m_pos_y = y;

    m_width = texture.getWidth();
    m_height = texture.getHeight();

    //Initialize the velocity
    m_vel_x = 0;
    m_vel_y = 0;

    //Cargo el vector con cada sprite de la cabeza
    for (int i = 0; i < TOTAL_HEAD_SPRITE; ++i) {
        m_head_sprite_clips[i] = {i * HUMANOID_HEAD_WIDTH, 0, HUMANOID_HEAD_WIDTH, HUMANOID_HEAD_HEIGHT};
    }

    m_face_orientation = FRONT_HEAD_SPRITE;
}

void SdlNPC::handleEvent(SDL_Event &e, int overload) {
    /*No utiliza velocidades y no depende del metodo move, lo resuelve aca*/
    if(e.type == SDL_KEYDOWN){
        switch(e.key.keysym.sym){
            case SDLK_UP:
                m_pos_y -= m_vel;
                m_face_orientation = BACK_HEAD_SPRITE;
                break;
            case SDLK_DOWN:
                m_pos_y += m_vel;
                m_face_orientation = FRONT_HEAD_SPRITE;
                break;
            case SDLK_LEFT:
                m_pos_x -= m_vel;
                m_face_orientation = LEFT_HEAD_SPRITE;
                break;
            case SDLK_RIGHT:
                m_pos_x += m_vel;
                m_face_orientation = RIGHT_HEAD_SPRITE;
                break;
        }
    }
}

void SdlNPC::handleEvent(SDL_Event &e) {
    //if a key was pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        //Adjust the velocity
        switch(e.key.keysym.sym){
            case SDLK_UP: m_vel_y -= m_vel; break;
            case SDLK_DOWN: m_vel_y += m_vel; break;
            case SDLK_LEFT: m_vel_x -= m_vel; break;
            case SDLK_RIGHT: m_vel_x += m_vel; break;

        }
    }
    //if key was released
    /*Cuando se suelta la tecla tenemos que deshacer los cambios*/
    if(e.type == SDL_KEYUP && e.key.repeat == 0){
        switch(e.key.keysym.sym){
            case SDLK_UP: m_vel_y += m_vel; break;
            case SDLK_DOWN: m_vel_y -= m_vel; break;
            case SDLK_LEFT: m_vel_x += m_vel; break;
            case SDLK_RIGHT: m_vel_x -= m_vel; break;

        }
    }
}

void SdlNPC::move(int screen_width, int screen_height) {
    //Move the dot left or right
    m_pos_x += m_vel_x;
    //if the dot went too far to the left or right
    if(m_pos_x < 0 || (m_pos_x + m_width > screen_width)){
        //Move back
        m_pos_x -= m_vel_x;
    }

    m_pos_y += m_vel_y;
    //if the dot went too far up or down
    if(m_pos_y < 0 || (m_pos_y + m_height > screen_height)){
        //Move back
        m_pos_y -= m_vel_y;
    }
}

void SdlNPC::render() {
    //Muestra la cabeza y el cuerpo del npc
    m_head_sprite_sheet_texture.render(m_pos_x + (m_body.getWidth() - HUMANOID_HEAD_WIDTH) / 2,
            m_pos_y - HUMANOID_HEAD_HEIGHT,
            &m_head_sprite_clips[m_face_orientation]);
    m_body.render(m_pos_x, m_pos_y);
}
