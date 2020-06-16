//
// Created by agustin on 16/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_CONSOLE_H
#define ARGENTUM_CLIENT_SDL_CONSOLE_H

#include "client_sdl_texture.h"

class SdlConsole {
private:
    SdlTexture& inputTexture;
    const SdlWindow& window;

    int console_x;
    int console_y;

    int width;
    int height;

    const int IMAGE_CONSOLE_X = 10;
    const int IMAGE_CONSOLE_Y = 24;
    const int IMAGE_CONSOLE_WIDTH = 764;
    const int IMAGE_CONSOLE_HEIGHT = 95;

public:
    SdlConsole(int screen_width, int screen_height,
            const SdlWindow &window, SdlTexture& inputTexture);

    /*Handle*/
    void handleEvents(const SDL_Event &event);

    /*Logic*/
    void execute();

    /*Render*/
    void render();
};


#endif //ARGENTUM_CLIENT_SDL_CONSOLE_H
