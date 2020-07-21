//
// Created by agustin on 4/7/20.
//

#include "client_sdl_text.h"

SdlText::SdlText(const int x,const int y, const std::string text, TTF_Font *font, const SdlWindow &window,
        const SDL_Color color) :
    font(font),
    text_color(color),
    rendered_text(text, font, color, window)
    {}

void SdlText::update(const std::string new_text) {
    rendered_text.loadFromRenderedText(new_text, text_color, font);
}

void SdlText::render(const int x, const int y) {
    rendered_text.render(x,y);
}

