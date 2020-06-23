//
// Created by agustin on 16/6/20.
//

#include <iostream>
#include "client_sdl_console.h"
#include "client_sdl_window.h"
#include "client_command.h"

SdlConsole::SdlConsole(const int screen_width, const int screen_height, const SdlWindow &window, TTF_Font *font,
                       SdlPlayer &player) :
        inputTexture("Enter Text!", font,SDL_Color{0xAA,0xAA,0xFF,0xFF}, window),
        window(window),
        player(player),
        text_color{0xAA,0xAA,0xFF,0xFF},
        font(font), render_text(false), return_times_pressed(0),
        X_FROM_PLAYER(IMAGE_CONSOLE_X - (screen_width / 2)),
        Y_FROM_PLAYER((screen_height / 2) - IMAGE_CONSOLE_Y){

    //Enable text input
    SDL_StartTextInput();

    this->console_x = player.getPosX() - X_FROM_PLAYER;
    this->console_y = player.getPosY() - Y_FROM_PLAYER;
    this->width = IMAGE_CONSOLE_WIDTH;
    this->height = IMAGE_CONSOLE_HEIGHT;
}

void SdlConsole::handleEvents(const SDL_Event &e) {
    render_text = false;
    return_times_pressed = 0;
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Handle backspace
        if (e.key.keysym.sym == SDLK_BACKSPACE && input_text.length() > 0) {
            //lop off character
            input_text.pop_back();
            this->render_text = true;
        } //handle copy
        else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
            SDL_SetClipboardText(input_text.c_str());
        } //Handle paste
        else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
            input_text = SDL_GetClipboardText();
            render_text = true;
        } else if (e.key.keysym.sym == SDLK_RETURN && input_text.length() > 0) {
            render_text = true;
            return_times_pressed += 1;
            std::cout << return_times_pressed << std::endl;
        }
    } else if (e.type == SDL_TEXTINPUT){
        //Not copy or pasting
        if(!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' ||
                                                  e.text.text[0] == 'v' || e.text.text[0] == 'V'))){
                //Append character
                input_text += e.text.text;
                render_text = true;
        }
    }
}

void SdlConsole::execute(SdlCamera &camera, BlockingQueue<std::unique_ptr<Message>> &clientEvents) {
    console_x = player.getPosX() - X_FROM_PLAYER - camera.getX();
    console_x = player.getPosY() - Y_FROM_PLAYER - camera.getY();
    //Rerender text if needed
    if(return_times_pressed > 0){
        std::cout << "emplacing" << std::endl;
        recentInputs.emplace_back(input_text, font, text_color, window);
        /**Al apretar enter resuelvo si es un comando valido*/
        this->sendCommandIfValid(clientEvents);
        input_text = " ";
        inputTexture.loadFromRenderedText(" ", text_color, font);
        return_times_pressed--;
        if(recentInputs.size() > 5){
            recentInputs.pop_front();
        }
    } else if(render_text){
        //Text is not empty
        if(!input_text.empty()){
            //Render new text
            inputTexture.loadFromRenderedText(input_text, text_color, font);
        }
            //Text is empty
        else {
            //Render space texture (SDL no permite string vacios)
            inputTexture.loadFromRenderedText(" ", text_color, font);
        }
    }
}

void SdlConsole::render() {
    SDL_Rect outline_rect = {console_x, console_y, width, height};
    SDL_SetRenderDrawColor(window.getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawRect(window.getRenderer(), &outline_rect);
    /*Renderizo los mensajes anteriores*/
    int i=0;
    for(auto & recent_input: recentInputs){
        i++;
        recent_input.render(console_x, console_y + (recent_input.getHeight() / 2) * i);
    }
    /*Renderizo lo que estoy escribiendo*/
    this->inputTexture.render(console_x, console_y * 4);
}

void SdlConsole::sendCommandIfValid(BlockingQueue<std::unique_ptr<Message>>& clientEvents) {
    Command* cmd = commandFactory.get(this->input_text);
    if(cmd){
        (*cmd)(clientEvents, 0);
        delete cmd;
        cmd = nullptr;
    }
}
