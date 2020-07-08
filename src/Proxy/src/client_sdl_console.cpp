//
// Created by agustin on 16/6/20.
//

#include <iostream>
#include "client_sdl_console.h"
#include "client_sdl_window.h"
#include "client_command.h"
#include "common_message.h"
#include "client_sdl_inventory.h"
#include "client_sdl_dynamic_renderable.h"

SdlConsole::SdlConsole(const SdlWindow &window, TTF_Font *font) :
        inputTexture("Enter Text!", font,SDL_Color{0xAA,0xAA,0xFF,0xFF}, window),
        window(window),
        text_color{0xAA,0xAA,0xFF,0xFF},
        server_message_color{0xAA,0xFF,0x33, 0xFF},
        font(font), render_text(false), return_times_pressed(0){

    //Enable text input
    SDL_StartTextInput();

    this->console_x = IMAGE_CONSOLE_X;
    this->console_y = IMAGE_CONSOLE_Y;
    this->width = window.getWidth() * 0.75;
    this->height = window.getHeight() * 0.125;
    /*this->width = IMAGE_CONSOLE_WIDTH;
    this->height = IMAGE_CONSOLE_HEIGHT;
    */
}

void SdlConsole::handleEvent(const SDL_Event &event, bool &is_event_handled) {
    render_text = false;
    return_times_pressed = 0;
    if (event.type == SDL_KEYDOWN) {
        //Handle backspace
        if (event.key.keysym.sym == SDLK_BACKSPACE && input_text.length() > 0) {
            //lop off character
            input_text.pop_back();
            this->render_text = true;
        } //handle copy
        else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
            SDL_SetClipboardText(input_text.c_str());
        } //Handle paste
        else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
            input_text = SDL_GetClipboardText();
            render_text = true;
        } else if (event.key.keysym.sym == SDLK_RETURN && input_text.length() > 0) {
            render_text = true;
            return_times_pressed += 1;
        }
    } else if (event.type == SDL_TEXTINPUT){
        //Not copy or pasting
        if(!(SDL_GetModState() & KMOD_CTRL && (event.text.text[0] == 'c' || event.text.text[0] == 'C' ||
                                               event.text.text[0] == 'v' || event.text.text[0] == 'V'))){
            //Append character
            input_text += event.text.text;
            render_text = true;
        }
    }
}

void SdlConsole::execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlMouse &mouse, SdlCamera &camera,
                         const SDL_Point player_pos) {
    //Rerender text if needed
    if(return_times_pressed > 0){
        recentInputs.emplace_back(input_text, font, text_color, window);
        this->sendCommandIfValid(clientEvents, mouse, camera, player_pos);
        input_text = "";
        inputTexture.loadFromRenderedText(" ", text_color, font);
        return_times_pressed--;
        if(recentInputs.size() > MAX_OUTPUTS){
            recentInputs.pop_front();
        }
    } else if(render_text){
        if(!input_text.empty()){
            inputTexture.loadFromRenderedText(input_text, text_color, font);
        }
        else {
            //Render space texture (SDL no permite string vacios)
            inputTexture.loadFromRenderedText(">>", text_color, font);
        }
    }
}

void SdlConsole::sendCommandIfValid(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlMouse &mouse,
                                    SdlCamera &camera, const SDL_Point player_pos) {
    /**Mouse sirve para los comandos que requieren pos del mouse, el /tomar requiere posicion player
     * pasar player por referencia?*/
    /**Primero el click luego el comando*/
    /*Command* cmd = commandFactory.get(this->input_text, mouse.getX(), mouse.getY());
    if(cmd){
        (*cmd)(clientEvents, 0);
        delete cmd;
        cmd = nullptr;
    }*/

    /**SOBRECARGO EL CONSTRUCTOR DE EXECUTECommand*/
    SDL_Point serverCoordinates = mouse.getPosition();
    bool clicked_in_map = mouse.clickedInMap();
    if (input_text == "/meditar") {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text)));
    } else if (input_text == "/resucitar" && clicked_in_map) {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, serverCoordinates.x, serverCoordinates.y)));
    } else if (input_text == "/resucitar") {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, -1, -1)));
    } else if (input_text == "/curar" && clicked_in_map) {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, serverCoordinates.x, serverCoordinates.y)));
    } else if (input_text.find("/depositar") == 0 && clicked_in_map) {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, serverCoordinates.x, serverCoordinates.y)));
    } else if (input_text.find("/retirar") == 0 && clicked_in_map) {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, serverCoordinates.x, serverCoordinates.y)));
    } else if (input_text == ("/listar") && clicked_in_map) {
        //mediator->notify(this, input_text);
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, serverCoordinates.x, serverCoordinates.y)));
    } else if (input_text.find("/comprar") == 0 && clicked_in_map) {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, serverCoordinates.x, serverCoordinates.y)));
    } else if (input_text.find("/vender") == 0 && clicked_in_map) {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, serverCoordinates.x, serverCoordinates.y)));
    } else if (input_text == ("/tomar")) {
        SDL_Point player_server_pos = camera.posToServerCoordinates(player_pos);
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, player_server_pos.x, player_server_pos.y)));
    } else if (input_text == ("/tirar")) {
        clientEvents.push(std::unique_ptr<Message> (new ExecuteCommand(input_text, mouse.getLastClickedItemIndex(),-1)));
    } else if (input_text.find('@') == 0) {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text)));
    }
    mouse.clear();
}

/*Agrega los mensajes del server al consola y reproduce los sonidos correspondiente a los mensajes*/
void SdlConsole::updateOutput(std::vector<std::string> outputs, SdlAudioManager &audioManager) {
    for(auto it = outputs.begin(); it != outputs.end(); it++){
        audioManager.reproduceRelatedSound(*it);
        if((int)(*it).size() > width / (int) MAX_OUTPUTS){
            std::string first_half_input = (*it).substr(0,(*it).size() / 2);
            std::string second_half_input = (*it).substr((*it).size() / 2 + 1,(*it).size());
            recentInputs.emplace_back(first_half_input, font, server_message_color, window);
            if(recentInputs.size() > MAX_OUTPUTS){
                recentInputs.pop_front();
            }
            recentInputs.emplace_back(second_half_input, font, server_message_color, window);
        } else {
            recentInputs.emplace_back(*it, font, server_message_color, window);
        }
        if(recentInputs.size() > MAX_OUTPUTS){
            recentInputs.pop_front();
        }
    }
}


void SdlConsole::render() {
    SDL_Rect outline_rect = {console_x, console_y, width, height};
    SDL_SetRenderDrawColor(window.getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawRect(window.getRenderer(), &outline_rect);
    SDL_Rect background = {console_x, console_y, width, height};
    SDL_SetRenderDrawColor(window.getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(window.getRenderer(), &background);

    /*Renderizo los mensajes anteriores*/
    int i=0;
    auto reverseIt = recentInputs.rbegin();
    for(; reverseIt != recentInputs.rend(); reverseIt++){
        i++;
        reverseIt->render(console_x,  height - (reverseIt->getHeight() / 2) * i);
    }
    this->inputTexture.render(console_x, height);

}
