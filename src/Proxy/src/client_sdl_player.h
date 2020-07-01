//
// Created by agustin on 8/6/20.
//

#ifndef SDLTEST_SDL_NPC_H
#define SDLTEST_SDL_NPC_H

#include <SDL2/SDL_image.h>
#include <vector>
#include "common_blocking_queue.h"
#include "common_proxy_socket.h"
#include "client_protected_list.h"
#include "client_sdl_camera.h"
#include "client_sdl_texture.h"
#include "common_message_structs.h"
#include "client_sdl_texture_manager.h"

class Message;
class SdlTexture;
class SdlPlayer {
private:
    SdlTextureManager& textureManager;

    //Dimensiones del jugador
    int width;
    int height;

    int pos_x, pos_y;

    SdlTextureManager::e_body_orientation body_or;
    SdlTextureManager::e_head_orientation head_or;

    SdlTextureManager::t_player_appearance t_appearance;

public:
    //Initializes the variables
    explicit SdlPlayer(SdlTextureManager &textureManager);

    void render(SdlCamera &camera);

    void updatePos(int player_x, int player_y, SdlCamera &camera);

    void updateEquipment(const equipment_t& equipment);

    int getPosX() const;

    int getPosY() const;
};


#endif //SDLTEST_SDL_NPC_H
