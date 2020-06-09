/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "dot.h"
#include "sdl_texture.h"
#include "sdl_window.h"
#include "sdl_npc.h"

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
        SdlTexture head_sprite_sheet("../../Cliente/sdl/assets/2005.gif", window);
        SdlTexture texture("../../Cliente/sdl/assets/340.gif", window);
        //Cargo fondo
        window.initPNG();
        SdlTexture background(SCREEN_WIDTH, SCREEN_HEIGHT, "../../Cliente/sdl/assets/dungeon.png", window);
        //Main loop flag
        bool quit = false;
        //Event handler
        SDL_Event e;

        SdlNPC npc(100,100, texture, head_sprite_sheet);

        /*The dot that will be moving around on the screen
        Dot dot(0, 0, texture);
        The dot that will be collided against
        Dot otherDot(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, texture);
        */

        //Inicializo ttf para poder renderizar texto
        if(TTF_Init() < 0) {
            //INICIALIZARIA TTF EN EL MAIN YA QUE PODRIA TENER MUCHAS LABELS DE TEXTO
            //ENTONCES NO DEBERIA INICIALIZARLO CADA VEZ QUE CREO UN LABEL
            //throw SdlException("Could not initialize TTF", TTF_GetError());
            return -1;
        }
        //ACORDARSE DE AGREGAR EL FINISH AL FINAL
        SDL_StartTextInput();
        SdlTexture label("Argentum", "../../Cliente/sdl/assets/AbyssinicaSIL-R.ttf",
                {255,0,0,0},100, 50,  window);

        //While application is running
        while (!quit) {
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                //User request quit
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                //Handle input for the dot
                npc.handleEvent(e,0);
            }
            //Muevo el npc, no usar en el caso del handleEvent con overload
            //npc.move(SCREEN_WIDTH, SCREEN_HEIGHT);

            //Pinto el fondo gris
            //window.fill();

            //Renderizo background
            background.render(0,0);

            //Renderizo el texto
            label.render(0,0);

            //Render objects
            npc.render();

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
    SDL_StopTextInput();
    IMG_Quit();
    SDL_Quit();
}
