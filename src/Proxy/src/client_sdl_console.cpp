//
// Created by agustin on 16/6/20.
//

#include <iostream>
#include "client_sdl_console.h"
#include "client_sdl_window.h"
#include "client_command.h"
#include "common_message.h"
#include "client_sdl_inventory.h"

/* {"espada", "hacha", "martillo", "vara de fresno",
"flauta elfica", "baculo nudoso", "baculo engarzado", "arco simple", "arco compuesto", "armadura de cuero",
"armadura de placas, tunica azul, capucha, casco de hierro, escudo de tortuga, escudo de hierro, sombrero magico"}
*/

SdlConsole::SdlConsole(const int screen_width, const int screen_height, const SdlWindow &window, TTF_Font *font,
                       SdlPlayer &player) :
        inputTexture("Enter Text!", font,SDL_Color{0xAA,0xAA,0xFF,0xFF}, window),
        window(window),
        player(player),
        text_color{0xAA,0xAA,0xFF,0xFF},
        font(font), render_text(false), return_times_pressed(0){

    //Enable text input
    SDL_StartTextInput();

    this->console_x = IMAGE_CONSOLE_X;
    this->console_y = IMAGE_CONSOLE_Y;
    this->width = IMAGE_CONSOLE_WIDTH;
    this->height = IMAGE_CONSOLE_HEIGHT;
}

void SdlConsole::handleEvent(const SDL_Event &event, bool &is_event_handled) {
    render_text = false;
    return_times_pressed = 0;
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
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
                         SdlInventory &inventory) {
    //Rerender text if needed
    if(return_times_pressed > 0){
        recentInputs.emplace_back(input_text, font, text_color, window);
        /**Al apretar enter resuelvo si es un comando valido*/
        /**TODO: comandos compuestos, que incluyen clicks*/
        this->sendCommandIfValid(clientEvents, mouse, camera, inventory);
        input_text = "";
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

void SdlConsole::sendCommandIfValid(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlMouse &mouse,
                                    SdlCamera &camera, SdlInventory &inventory) {
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
    } else if (input_text == "/curar" && clicked_in_map) {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, serverCoordinates.x, serverCoordinates.y)));
    } else if (input_text.find("/depositar") == 0 && clicked_in_map) {
        /*si el comando empieza con depositar e hizo click, envio el input entero y el server lo valida*/
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, serverCoordinates.x, serverCoordinates.y)));
    } else if (input_text.find("/retirar") == 0 && clicked_in_map) {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, serverCoordinates.x, serverCoordinates.y)));
    } else if (input_text == ("/listar") && clicked_in_map) {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, serverCoordinates.x, serverCoordinates.y)));
    } else if (input_text.find("/comprar") == 0 && clicked_in_map) {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, serverCoordinates.x, serverCoordinates.y)));
    } else if (input_text.find("/vender") == 0 && clicked_in_map) {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, serverCoordinates.x, serverCoordinates.y)));
    } else if (input_text == ("/tomar")) {
        SDL_Point player_server_pos = camera.toServerCoordinates(SDL_Point{player.getPosX(), player.getPosY()});
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text, player_server_pos.x, player_server_pos.y)));
    } else if (input_text == ("/tirar") && clicked_in_map) {
        //clientEvents.push(std::unique_ptr<Message> (new ExecuteCommand(input_text, inventory.getLastCickedIndex())));
    } else if (input_text.find("@") == 0) {
        clientEvents.push(std::unique_ptr<Message>(new ExecuteCommand(input_text)));
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
