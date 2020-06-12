//Using SDL, SDL_image, standard math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
#include "client_sdl_texture.h"
#include "client_sdl_window.h"
#include "client_sdl_player.h"
#include "common_blocking_queue.h"

//Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//Frees media and shuts down SDL
void close();

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
        //Main loop flag
        bool quit = false;
        //Event handler
        SDL_Event e;

        BlockingQueue<int> proxySocket;

        SdlPlayer player(100, 100, texture, head_sprite_sheet);

        /*The dot that will be moving around on the screen
        Dot dot(0, 0, texture);
        The dot that will be collided against
        Dot otherDot(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, texture);
        */

        //While application is running
        while (!quit) {
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                //User request quit
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                //Handle input for the dot
                player.handleEvent(e, 0);
                proxySocket.push(5);
                std::cout << proxySocket.pop() << std::endl;
            }
            //Muevo el player, no usar en el caso del handleEvent con overload
            //player.move(SCREEN_WIDTH, SCREEN_HEIGHT);

            //Pinto el fondo gris
            //window.fill();

            //Renderizo background
            background.render(0,0);

            //Render objects
            player.render();

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

void close(){
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
