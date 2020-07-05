//
// Created by agustin on 26/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_BAR_H
#define ARGENTUM_CLIENT_SDL_BAR_H


#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "client_sdl_camera.h"

class SdlWindow;
class SdlBar {
private:
    /*son constantes si la imagen es estatica*/
    const int X;
    const int Y;

    const int WIDTH = 120;
    const int HEIGHT = 10;

    SDL_Color bar_color;
    SDL_Rect bar;
    SDL_Rect outline_bar;
    SDL_Renderer* renderer;


public:
    SdlBar(const int x, const int y, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const SdlWindow& window);

    SdlBar(const int x, const int y, const int w, const int h, const uint8_t r, const uint8_t g, const uint8_t b,
           const uint8_t a, const SdlWindow &window);

    void render();

    void update(const float percentage);

    void render(const int x, const int y);
};


#endif //ARGENTUM_CLIENT_SDL_BAR_H
