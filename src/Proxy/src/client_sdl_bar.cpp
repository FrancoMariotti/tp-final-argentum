//
// Created by agustin on 26/6/20.
//

#include "client_sdl_bar.h"
#include "client_sdl_window.h"

SdlBar::SdlBar(const int x, const int y, const uint8_t r, const uint8_t g,
        const uint8_t b, const uint8_t a, const SdlWindow &window) :
    X(x),
    Y(y),
    bar_color{r,g,b,a},
    bar{x, y, WIDTH, HEIGHT},
    outline_bar{x, y, WIDTH, HEIGHT},
    renderer(window.getRenderer()){


}

/*Cambio el ancho de la barra opaca segun el porcentaje*/
void SdlBar::update(const float percentage){
    bar.w = WIDTH * percentage;
}

void SdlBar::render() {
    SDL_SetRenderDrawColor(renderer, bar_color.r, bar_color.g, bar_color.b, bar_color.a);
    SDL_RenderDrawRect(renderer, &this->outline_bar);
    SDL_SetRenderDrawColor(renderer, bar_color.r, bar_color.g, bar_color.b, bar_color.a);
    SDL_RenderFillRect(renderer, &this->bar);
}