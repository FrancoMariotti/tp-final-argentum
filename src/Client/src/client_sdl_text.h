//
// Created by agustin on 4/7/20.
//

#ifndef ARGENTUM_CLIENT_SDL_TEXT_H
#define ARGENTUM_CLIENT_SDL_TEXT_H


#include "client_sdl_texture.h"

class SdlText {
private:
    TTF_Font* font;
    SDL_Color text_color;
    SdlTexture rendered_text;
public:
    /*Sirve para renderizar un texto que se va a mantener constante*/
    SdlText(int x, int y, std::string text, TTF_Font* font, const SdlWindow& window, SDL_Color color );

    /*Carga y renderiza el nuevo texto en las nuevas posicion x e y*/
    void update(const std::string new_text);

    /*Renderiza el texto cargado y posicion actual*/
    void render(const int x,const int y);

};


#endif //ARGENTUM_CLIENT_SDL_TEXT_H
