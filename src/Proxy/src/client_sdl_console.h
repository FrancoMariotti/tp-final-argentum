//
// Created by agustin on 16/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_CONSOLE_H
#define ARGENTUM_CLIENT_SDL_CONSOLE_H

#include "client_sdl_texture.h"
#include "client_sdl_player.h"
#include "client_command_factory.h"
#include "client_sdl_mouse.h"
#include <list>

class SdlConsole {
private:
    SdlTexture inputTexture;
    const SdlWindow& window;
    const SdlPlayer& player;
    CommandFactory commandFactory;
    SDL_Color text_color;
    TTF_Font* font;
    std::string input_text;
    bool render_text;
    int return_times_pressed;

    int console_x;
    int console_y;

    int width;
    int height;

    const int IMAGE_CONSOLE_X = 12;
    const int IMAGE_CONSOLE_Y = 24;
    const int IMAGE_CONSOLE_WIDTH = 764;
    const int IMAGE_CONSOLE_HEIGHT = 95;

    std::list<SdlTexture> recentInputs;

public:
    SdlConsole(const int screen_width, const int screen_height, const SdlWindow &window, TTF_Font *font,
               SdlPlayer &player);

    /*Handle*/
    void handleEvent(const SDL_Event &event, bool &is_event_handled);

    /*Logic*/
    void execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlMouse &mouse);

    /*Render*/
    void render();

    void sendCommandIfValid(BlockingQueue<std::unique_ptr<Message>>& clientEvents, SdlMouse& mouse);
};


#endif //ARGENTUM_CLIENT_SDL_CONSOLE_H
