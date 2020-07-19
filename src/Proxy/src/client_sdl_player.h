//
// Created by agustin on 8/6/20.
//

#ifndef SDLTEST_SDL_NPC_H
#define SDLTEST_SDL_NPC_H

#include <SDL2/SDL_image.h>
#include <vector>
#include "Common/BlockingQueue.h"
#include "Common/common_proxy_socket.h"
#include "client_protected_list.h"
#include "client_sdl_camera.h"
#include "client_sdl_texture.h"
#include "Common/Messages/message_structs.h"
#include "client_sdl_texture_manager.h"
#include "client_sdl_timer.h"

class Message;
class SdlTexture;
class SdlPlayer {
private:
    SdlTextureManager& textureManager;

    //Dimensiones del jugador
    int width;
    int height;

    int pos_x, pos_y;
    int old_x, old_y;

    const int MAX_FRAMES = 4;
    int animation_frame;
    bool is_moving;

    SdlTextureManager::e_body_orientation body_or;
    SdlTextureManager::e_head_orientation head_or;

    SdlTextureManager::t_player_appearance t_appearance;
public:
    explicit SdlPlayer(SdlTextureManager &textureManager);

    void render(SdlCamera &camera, SdlTimer &timer);

    void updatePos(int player_x, int player_y, SdlCamera &camera);

    void updateEquipment(const equipment_t& equipment);

    int getPosX() const;

    int getPosY() const;

    void startAnimation();

    void endAnimationIfComplete();
};


#endif //SDLTEST_SDL_NPC_H
