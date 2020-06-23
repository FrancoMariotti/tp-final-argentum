//
// Created by agustin on 13/6/20.
//

#include <thread>
#include "client_client.h"
#include "client_sdl_inventory.h"
#include "client_sdl_console.h"
#include "common_message.h"
#include "client_protected_list.h"
#include "client_sdl_world.h"

//Screen dimension constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

//The dimensiones of the level
const int LEVEL_WIDTH = 3200;
const int LEVEL_HEIGHT = 3200;

#define FONT_SIZE 14

Client::Client(ProxySocket& proxySocket) :
        window(SCREEN_WIDTH, SCREEN_HEIGHT),
        font(nullptr),
        proxySocket(proxySocket),
        thSend(clientEvents, proxySocket),
        thRecv(serverEvents,proxySocket)
    {
    //Permito la carga del PNGs
    window.initPNG();
    window.initTTF();
    //Abro la fuente
    this->font = TTF_OpenFont("../../Proxy/assets/nakula.ttf", FONT_SIZE);
    if (!font){
        //throw SdlException("Could not open font in function", TTF_GetError());
    }
    /*Lanzo los threads*/
    thSend.start();
    thRecv.start();

    }

int Client::run() {
    //Cargo las texturas del personaje
    SdlTexture head_sprite_sheet(17,15,"../../Proxy/assets/2005.gif", window);
    SdlTexture texture("../../Proxy/assets/340.gif", window);

    //Cargo el personaje
    SdlPlayer player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, texture, head_sprite_sheet);

    SdlTexture mainInterface(LEVEL_WIDTH, LEVEL_HEIGHT,
            "../../Proxy/assets/bg.png", window);

    //Creo camara
    SdlCamera camera(SCREEN_WIDTH, SCREEN_HEIGHT, player);

    //Cargo la consola
    SdlConsole console(SCREEN_WIDTH, SCREEN_HEIGHT, window, font, player);

    //Cargo el inventario
    SdlInventory inventory(SCREEN_WIDTH, SCREEN_HEIGHT, window, player);

    //Cargo el mundo
    SdlWorld world(window);

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;

    //this->handleServerEvents(world);
    for (int i = 0; i < 100 ; ++i) {
        for (int j = 0; j < 100 ; ++j) {
            if(i == j){
                world.add(i, j, "hongo");
            } else {
                world.add(i, j, "pasto");
            }
        }
    }
    ///

    //While application is running
    while (!quit) {
        //Consume serverEvents list (actualizar el modelo)

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
            console.handleEvents(event);

            //Handle de los botones
            inventory.handleEvents(event);
        }
        /*Logic*/
        player.move(clientEvents,serverEvents);
        inventory.use(clientEvents);
        console.execute();
        camera.move();

        //Limpio pantalla
        window.fill(0xFF, 0xFF, 0xFF, 0xFF);

        //Renderizo mainInterface
        mainInterface.render(0, 0);

        //Render objects
        world.render(camera);
        player.render();
        inventory.render();
        console.render();

        //Update screen
        window.render();

        //Cap FPS 50
        SDL_Delay(20);
    }
    return 0;
}

void Client::stop() {
    thSend.stop();
    thRecv.stop();
    thSend.join();
    thRecv.join();
}

Client::~Client() {

    if(font){
        TTF_CloseFont(font);
    }
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

void Client::handleServerEvents(SdlWorld& world) {
    /**al consumir la lista solo se dibuja en el primer frame pero en el siguiente frame la lista ya no esta
     * por lo tanto debo guardar estos mensajes para redibujarlo en cada render*/
    std::list<std::unique_ptr<Message>> messages = this->serverEvents.consume();
    for(auto & msg : messages){
        if(msg->getId() == 'd'){
            world.add( msg->getTileX(), msg->getTileY(), msg->getTileName());
        } else if(msg->getId() == 'p'){
            /**Init de la posicion del jugador*/
        }
    }

}
