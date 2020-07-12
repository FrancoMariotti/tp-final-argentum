//
// Created by agustin on 12/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_BUTTON_H
#define ARGENTUM_CLIENT_SDL_BUTTON_H

#include <SDL2/SDL_events.h>
#include "client_sdl_texture.h"
#include "common_blocking_queue.h"
#include "client_command.h"
#include "common_proxy_socket.h"
#include "client_sdl_camera.h"
#include "client_sdl_mouse.h"
#include "client_sdl_text.h"
#include "client_event_mediator.h"

class SdlText;
class Message;
class SdlButton {
private:
    enum e_outline_sprite{
        OUTLINE_SPRITE_MOUSE_OVER_MOTION,
        OUTLINE_SPRITE_MOUSE_OUT,
        OUTLINE_SPRITE_BUTTON_CLICKED,
        OUTLINE_SPRITE_TOTAL,
    };

    int width;
    int height;
    int left_click;
    int right_click;
    bool sprite_locked;
    const std::string texture_id;
    SDL_Point position;
    //Currently used sprite
    e_outline_sprite outline_sprite;
    //Sprites de cada estado del boton
    std::vector<SDL_Rect> outline_sprite_clips;
    //Imagen del boton
    SdlTexture& buttonSpriteSheetTexture;
    SdlTexture& outlineTexture;
    SdlText buttonText;
    UseItemCommand cmd;

public:
    SdlButton(SdlTexture &buttonTexture, SdlTexture &outlineTexture, TTF_Font *font, const SdlWindow &window,
              const std::string texture_id);

    SdlButton(const SdlButton& other) = delete;

    SdlButton(SdlButton&& other) noexcept;

    void setPosition(int x, int y);
    //Handles mouse event
    void handleEvent(SDL_Event &e, bool &is_event_handled);
    /*Si el jugador hizo click en algun item envia el comando a la cola de eventos*/
    void use(BlockingQueue<std::unique_ptr<Message>> &clientEvents, int i, SdlMouse &mouse, SdlInventory *inventory);
    /*Muestra los sprites de los botones*/
    void render();
    ~SdlButton() = default;

    void updateText(const equipment_t &equipment);

    void lockOutlineSprite(const bool lock);
};


#endif //ARGENTUM_CLIENT_SDL_BUTTON_H
