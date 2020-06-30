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
    enum e_head_orientation{
        FRONT_HEAD_SPRITE,
        RIGHT_HEAD_SPRITE,
        LEFT_HEAD_SPRITE,
        BACK_HEAD_SPRITE,
        TOTAL_HEAD_SPRITE
    };

    enum orientation{
        FRONT,
        BACK,
        LEFT,
        RIGHT,
        TOTAL_ORIENTATIONS,
    };

    SdlTexture& armourSpriteSheetTexture;
    SdlTexture& headSpriteSheetTexture;
    SdlTexture& weaponSpriteSheetTexture;
    SdlTexture& shieldSpriteSheetTexture;

    //Dimensiones del jugador
    //int width;
    //int height;
    //Se puede mover un casillero a la vez
    const int VEL = 1;
    int pos_x, pos_y;

    //Offset del movimiento
    int vel_x, vel_y;

    SDL_Rect armour_orientation_clips[TOTAL_HEAD_SPRITE];
    SDL_Rect head_orientation_clips[TOTAL_HEAD_SPRITE];
    SDL_Rect weapon_orientation_clips[TOTAL_HEAD_SPRITE];
    SDL_Rect shield_orientation_clips[TOTAL_HEAD_SPRITE];

    enum e_head_orientation e_face_orientation;
    enum orientation e_body_orientation;

public:
    //Initializes the variables
    SdlPlayer(SdlWindow &window, SdlTextureManager &textureManager);

    //client side: Ajusta la velocidad del jugador
    void handleEvent(SDL_Event &e, bool &is_event_handled);

    void move(BlockingQueue<std::unique_ptr<Message>> &clientEvents);
    //Muestra al jugador en pantalla

    void render(SdlCamera &camera);

    void update(const int player_x, const int player_y, SdlCamera &camera);

    int getPosX() const;

    int getPosY() const;

    void update();

    void update(SdlTexture &newWeaponSheet, SdlTexture &newShieldSheet);
};


#endif //SDLTEST_SDL_NPC_H
