//
// Created by agustin on 13/6/20.
//

#include "client_client.h"
#include "client_sdl_inventory.h"

//Screen dimension constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define FONT_SIZE 18

Client::Client() :
    window(SCREEN_WIDTH, SCREEN_HEIGHT),
    background(SCREEN_WIDTH, SCREEN_HEIGHT, "../../Proxy/interfaces/VentanaPrincipal.jpg", window)
    {
    //Permito la carga del PNGs
    window.initPNG();
    window.initTTF();
}

int Client::run() {
    //Cargo las texturas del personaje
    SdlTexture head_sprite_sheet(17,15,"../../Proxy/assets/2005.gif", window);
    SdlTexture texture("../../Proxy/assets/340.gif", window);

    //Abro la fuente
    TTF_Font* font = TTF_OpenFont("../../Proxy/assets/nakula.ttf", FONT_SIZE);
//    if (!font) {
  //      throw SdlException("Could not open font in function", TTF_GetError());
   // }

    //The current input text
    SDL_Color textColor = {0xAA,0xAA,0xFF,0xFF};
    std::string inputText = "Some Really large Text";
    SdlTexture inputTextTexture(inputText, font, textColor, window);

    //Cargo la consola
    //SdlConsole console;

    //Cargo el inventario
    SdlInventory inventory(SCREEN_WIDTH,SCREEN_HEIGHT,window);

    //Cargo el personaje
    SdlPlayer player(100, 100, texture, head_sprite_sheet);

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;

    //While application is running
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&event) != 0) {
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                    /*test*/
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_h){
                        inventory.addItem("16055");
                    }
                    break;
            }
            //Handle del jugador
            player.handleEvent(event);

            //Handle entrada
            //console.handleEvent(event) input del teclado para los comandos e.g resucitar

            //Handle de los botones
            inventory.handleEvents(&event, proxySocket);
        }

        /*Logic*/
        player.move(proxySocket);
        inventory.use(proxySocket);

        //Limpio pantalla
        window.fill(0xFF, 0xFF, 0xFF, 0xFF);

        //Renderizo background
        background.render(0,0);

        //Render objects
        player.render();
        inventory.render();
        inputTextTexture.render(10, 24);

        //Update screen
        window.render();

        //Cap FPS
        SDL_Delay(16);
    }
    //Close SDL
    this->close();
}


void Client::close(){
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();


}


/*Proxy del socket, se llama cada vez que el jugador mueve al personaje
 * recibe un struct con el offset*/
void proxyServerRecieve(BlockingQueue<t_command> &read, BlockingQueue<t_command> &write) {
    t_command move = read.pop();
    std::cout << "movimiento en x:" << move.x << "\n movimiento en y:" << move.y
              << std::endl;
    //if movimiento valido
    t_command response;
    response.command = "move";
    response.x = move.x;
    response.y = move.y;
    //else response = {"move", 0, 0};
    write.push(response);
}

