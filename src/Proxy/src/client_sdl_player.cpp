//
// Created by agustin on 8/6/20.
//

#include <iostream>
#include "client_sdl_player.h"
#include "client_sdl_texture.h"

#define HUMANOID_HEAD_WIDTH 17
#define HUMANOID_HEAD_HEIGHT 15

SdlPlayer::SdlPlayer(int x, int y, SdlTexture &texture, SdlTexture &head) :
        bodyTexture(texture),
        headSpriteSheetTexture(head){
    //Initialize the offsets
    pos_x = x;
    pos_y = y;

    width = texture.getWidth();
    height = texture.getHeight();

    //Initialize the velocity
    vel_x = 0;
    vel_y = 0;

    //Cargo el vector con cada sprite de la cabeza
    for (int i = 0; i < TOTAL_HEAD_SPRITE; ++i) {
        head_sprite_clips[i] = {i * HUMANOID_HEAD_WIDTH, 0, HUMANOID_HEAD_WIDTH, HUMANOID_HEAD_HEIGHT};
    }

    e_face_orientation = FRONT_HEAD_SPRITE;
}

void SdlPlayer::handleEvent(SDL_Event &e, ProxySocket &proxySocket) {
    if(e.type == SDL_KEYDOWN){
        switch(e.key.keysym.sym){
            case SDLK_UP:
                e_face_orientation = BACK_HEAD_SPRITE;
                break;
            case SDLK_DOWN:
                e_face_orientation = FRONT_HEAD_SPRITE;
                break;
            case SDLK_LEFT:
                e_face_orientation = LEFT_HEAD_SPRITE;
                break;
            case SDLK_RIGHT:
                e_face_orientation = RIGHT_HEAD_SPRITE;
                break;
        }
    }
}

void SdlPlayer::handleEvent(SDL_Event &e) {
    //if a key was pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        //Adjust the velocity
        switch(e.key.keysym.sym){
            case SDLK_UP: vel_y -= VEL; break;
            case SDLK_DOWN: vel_y += VEL; break;
            case SDLK_LEFT: vel_x -= VEL; break;
            case SDLK_RIGHT: vel_x += VEL; break;

        }
    }
    //if key was released
    /*Cuando se suelta la tecla tenemos que deshacer los cambios*/
    if(e.type == SDL_KEYUP && e.key.repeat == 0){
        switch(e.key.keysym.sym){
            case SDLK_UP: vel_y += VEL; break;
            case SDLK_DOWN: vel_y -= VEL; break;
            case SDLK_LEFT: vel_x += VEL; break;
            case SDLK_RIGHT: vel_x -= VEL; break;

        }
    }
}

/**Esto es para pruebas con la logica en el cliente*/
void SdlPlayer::move(int screen_width, int screen_height) {
    //Move the dot left or right
    pos_x += vel_x;

    std::cout << "pos_x: " << pos_x << "pos_y: " << pos_y << std::endl;
    std::cout << "vel_x: " << vel_x << "vel_y:" << vel_y << std::endl;

    //if the dot went too far to the left or right
    if(pos_x < 0 || (pos_x + width > screen_width)){
        //Move back
        pos_x -= vel_x;
    }

    pos_y += vel_y;
    //if the dot went too far up or down
    if(pos_y < 0 || (pos_y + height > screen_height)){
        //Move back
        pos_y -= vel_y;
    }
}

void SdlPlayer::render() {
    //Muestra la cabeza y el cuerpo del npc
    headSpriteSheetTexture.render(pos_x + (bodyTexture.getWidth() - HUMANOID_HEAD_WIDTH) / 2,
                                       pos_y - HUMANOID_HEAD_HEIGHT,
                                  &head_sprite_clips[e_face_orientation]);
    bodyTexture.render(pos_x, pos_y);
}

/**Logic*/
void SdlPlayer::move(ProxySocket &proxySocket) {

    /*Crea el msg con el offset al que se quiere mover, lo envia al server y
     * actualiza la posicion con la respuesta del server*/
    t_command player_movement={"m", vel_x, vel_y};
    proxySocket.writeToServer(player_movement);
    /**Debe ser readClient pero esto es para simular*/
    player_movement = proxySocket.readServer();

    pos_x += player_movement.x;
    pos_y += player_movement.y;
}
