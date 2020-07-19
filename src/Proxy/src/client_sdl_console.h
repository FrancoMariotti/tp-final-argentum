//
// Created by agustin on 16/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_CONSOLE_H
#define ARGENTUM_CLIENT_SDL_CONSOLE_H

#include "client_sdl_texture.h"
#include "client_sdl_player.h"
#include "client_sdl_mouse.h"
#include "client_sdl_inventory.h"
#include "client_sdl_audio_manager.h"
#include <list>

class SdlConsole : public BaseComponent {
private:
    SdlTexture inputTexture;
    const SdlWindow& window;
    SDL_Color text_color;
    SDL_Color server_message_color;
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
    unsigned long MAX_OUTPUTS;

    std::list<SdlTexture> recentInputs;

public:
    SdlConsole(const SdlWindow &window, TTF_Font *font);

    /*Handle*/
    void handleEvent(const SDL_Event &event, bool &is_event_handled);

    /*Logic*/
    void execute();

    void updateOutput(std::vector<std::string> outputs, SdlAudioManager &audioManager);

    /*Render*/
    void render();


};


#endif //ARGENTUM_CLIENT_SDL_CONSOLE_H
