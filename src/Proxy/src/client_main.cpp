//Using SDL, SDL_image, standard math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
#include "client_sdl_texture.h"
#include "client_sdl_window.h"
#include "client_sdl_player.h"
#include "common_blocking_queue.h"
#include "client_sdl_button.h"

//Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//Frees media and shuts down SDL
void close();

void proxyServerRecieve(BlockingQueue<t_movement> &read, BlockingQueue<t_movement> &write);

int main(int argc, char* args[]) {
    try {
        //Start up SDL and create window
        SdlWindow window(SCREEN_WIDTH,SCREEN_HEIGHT);
        //Load media
        SdlTexture head_sprite_sheet("../../Proxy/assets/2005.gif", window);
        SdlTexture texture("../../Proxy/assets/340.gif", window);
        //Cargo fondo
        window.initPNG();
        SdlTexture background(SCREEN_WIDTH, SCREEN_HEIGHT, "../../Proxy/assets/dungeon.png", window);

        //Botones
        std::vector<SdlButton> buttons;
        SdlTexture buttonSpriteSheet("../../Proxy/assets/button.png", window);
        for (int i = 0; i < 1 ; ++i) {
            buttons.emplace_back(300,200,buttonSpriteSheet);
        }

        //Main loop flag
        bool quit = false;
        //Event handler
        SDL_Event event;

        BlockingQueue<t_movement> proxyPeerSocket;
        BlockingQueue<t_movement> proxyClientSocket;

        SdlPlayer player(100, 100, texture, head_sprite_sheet);

        //While application is running
        while (!quit) {
            //Handle events on queue
            while (SDL_PollEvent(&event) != 0) {
                //User request quit
                switch(event.type){
                    case SDL_QUIT:
                        quit = true;
                        break;
                    case SDL_KEYDOWN:
                        //Handle input for the dot
                        player.handleEvent(event, proxyPeerSocket);
                        proxyServerRecieve(proxyPeerSocket, proxyClientSocket);
                        t_movement movement = proxyClientSocket.pop();
                        player.move(movement);
                        break;
                }
            }
            for(auto & button : buttons){
                button.handleEvent(&event);
            }
            //Renderizo background
            background.render(0,0);
            //Render objects
            player.render();
            //Renderizo botones
            for (auto & button : buttons) {
                button.render();
            }
            //Update screen
            window.render();
        }
        //Close SDL
        close();

    } catch (std::exception &e) {
        printf("%s", e.what());
    } catch (...){
        printf("%s", "Unknow error");
    }

}


/*Proxy del socket, se llama cada vez que el jugador mueve al personaje
 * recibe un struct con el offset*/
void proxyServerRecieve(BlockingQueue<t_movement> &read, BlockingQueue<t_movement> &write) {
    t_movement move = read.pop();
    std::cout << "movimiento en x:" << move.x << "\n movimiento en y:" << move.y
              << std::endl;
    //if movimiento valido
        t_movement response = {move.x, move.y};
    //else response = {0, 0};
    write.push(response);

}

void close(){
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
