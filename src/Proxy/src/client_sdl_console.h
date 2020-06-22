//
// Created by agustin on 16/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_CONSOLE_H
#define ARGENTUM_CLIENT_SDL_CONSOLE_H

#include "client_sdl_texture.h"
#include <list>

class SdlConsole {
private:
    SdlTexture inputTexture;
    const SdlWindow& window;
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
    SdlConsole(int screen_width, int screen_height, const SdlWindow &window, TTF_Font *font);

    /*Handle*/
    void handleEvents(const SDL_Event &event);

    /*Logic*/
    void execute();

    /*Render*/
    void render();

};


#endif //ARGENTUM_CLIENT_SDL_CONSOLE_H
