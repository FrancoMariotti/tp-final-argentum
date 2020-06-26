//
// Created by agustin on 26/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_OUTPUT_H
#define ARGENTUM_CLIENT_SDL_OUTPUT_H


#include <SDL2/SDL_ttf.h>
#include "client_sdl_texture.h"

class SdlOutput {
private:
    SDL_Color text_color;
    TTF_Font* font;
    const std::string LABEL;
    std::string output;
    SdlTexture outputTexture;

    const int X;
    const int Y;

public:
    SdlOutput(const int x,const int y,const SdlWindow& window, TTF_Font* font);

    void render();

    void update(const std::string &new_output);
};


#endif //ARGENTUM_CLIENT_SDL_OUTPUT_H
