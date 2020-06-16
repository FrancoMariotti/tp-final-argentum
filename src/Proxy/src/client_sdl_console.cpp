//
// Created by agustin on 16/6/20.
//

#include "client_sdl_console.h"

#define BASE_SCREEN_WIDTH 1024
#define BASE_SCREEN_HEIGHT 768

SdlConsole::SdlConsole(const int screen_width, const int screen_height,
        const SdlWindow &window, SdlTexture& inputTexture) :
        window(window),
        inputTexture(inputTexture){

    this->console_x = IMAGE_CONSOLE_X;
    this->console_y = IMAGE_CONSOLE_Y;
    this->width = IMAGE_CONSOLE_WIDTH;
    this->height = IMAGE_CONSOLE_HEIGHT;

}

void SdlConsole::handleEvents(const SDL_Event &event) {

}

void SdlConsole::execute() {

}

void SdlConsole::render() {
    this->inputTexture.render(console_x, console_y);
}
