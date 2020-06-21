//
// Created by agustin on 13/6/20.
//

#include <thread>
#include "client_client.h"
#include "client_sdl_inventory.h"
#include "client_sdl_console.h"
#include "common_message.h"
#include "client_protected_list.h"
#include "client_th_send.h"
#include "client_th_recv.h"
#include "client_sdl_world.h"

//Screen dimension constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define FONT_SIZE 14

Client::Client(ProxySocket& proxySocket) :
    window(SCREEN_WIDTH, SCREEN_HEIGHT),
    background(SCREEN_WIDTH, SCREEN_HEIGHT, "../../Proxy/interfaces/VentanaPrincipal.jpg", window),
    font(nullptr),
    proxySocket(proxySocket),
    thSend(clientEvents, proxySocket),
    thRecv(serverEvents, proxySocket)
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

    //Cargo la consola
    SdlConsole console(SCREEN_WIDTH, SCREEN_HEIGHT, window, font);

    //Cargo el inventario
    SdlInventory inventory(SCREEN_WIDTH,SCREEN_HEIGHT,window);

    //Cargo el personaje
    SdlPlayer player(100, 300, texture, head_sprite_sheet);

    //Cargo el mundo
    SdlWorld world(window);

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;

    //While application is running
    while (!quit) {
        //Consume serverEvents list (actualizar el modelo)
        //this->handleServerEvents(world);

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
        player.move(clientEvents);
        inventory.use(clientEvents);
        console.execute();

        //Limpio pantalla
        window.fill(0xFF, 0xFF, 0xFF, 0xFF);

        //Renderizo background
        background.render(0,0);

        //Render objects
        player.render();
        inventory.render();
        console.render();
        /**test, itero cada mensaje del server con x,y,id del dibujo*/
        world.render(200,200, 0);
        world.render(300,200, 1);
        world.render(400,200, 2);

        //Update screen
        window.render();

        //Cap FPS 50
        SDL_Delay(20);
    }

    return 0;
}

Client::~Client() {
    thSend.stop();
    thRecv.stop();
    thSend.join();
    thRecv.join();

    if(font){
        TTF_CloseFont(font);
    }
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

void Client::handleServerEvents(SdlWorld &world) {
    std::list<std::unique_ptr<Message>> messages = this->serverEvents.consume();
/*
    std::list<std::unique_ptr<Message>>::iterator iterator = messages.begin();
    while(iterator != messages.end()){
        if((*iterator)->getId() == 'd'){
            world.render( (*iterator)->getX(), (*iterator)->getY(), (*iterator)->getName() )
        }
    }
*/
 }
