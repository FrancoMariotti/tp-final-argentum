//
// Created by agustin on 13/6/20.
//

#include <thread>
#include "client_client.h"
#include "common_message.h"
#include "client_protected_list.h"

//Screen dimension constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

//The dimensiones of the level
const int LEVEL_WIDTH = 3200;
const int LEVEL_HEIGHT = 3200;

Client::Client(ProxySocket& proxySocket) :
        //window(SCREEN_WIDTH, SCREEN_HEIGHT),
        //font(nullptr),
        proxySocket(proxySocket),
        thSend(clientEvents, proxySocket),
        thRecv(serverEvents,proxySocket),
        gui(SCREEN_WIDTH, SCREEN_HEIGHT, clientEvents){
    /*Lanzo los threads*/
    thSend.start();
    thRecv.start();
}

int Client::run() {
    //Cargo el personaje
    /*SdlPlayer player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, window);

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
    */
    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;

    //this->init(world);
    for (int i = 0; i < 100 ; ++i) {
        for (int j = 0; j < 100 ; ++j) {
            if(i == j){
                gui.addTile(i, j, "hongo");
            } else {
                gui.addTile(i, j, "pasto");
            }
        }
    }
    gui.addNpc(200,200,"arania1");
    ///

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
                        gui.addItem("16055");
                    }
                    break;
            }
            gui.handleEvents(event);
        }
        /*Logic*/
        gui.execute();
        /*Consumo la lista de eventos del server y actualizo modelo*/
        this->update();

        //Limpio pantalla
        //window.fill(0xFF, 0xFF, 0xFF, 0xFF);

        //Renderizo mainInterface
        //mainInterface.render(0, 0);

        //Render objects
        gui.render();

        //Update screen
        //window.render();

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
}

void Client::update() {
    std::list<std::unique_ptr<Message>> messages = this->serverEvents.consume();
    for(auto & msg : messages){
        if(msg->getId() == 'm'){
            this->gui.update(msg->getPlayerVelX(), msg->getPlayerVelY());
        }
    }
}
