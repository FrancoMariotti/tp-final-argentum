//
// Created by agustin on 13/6/20.
//

#include <thread>
#include <random>
#include "client_client.h"
#include "common_message.h"
#include "client_protected_list.h"

//Screen dimension constants
#define SCREEN_WIDTH 1024//640
#define SCREEN_HEIGHT 768//480


Client::Client(ProxySocket& proxySocket) :
        proxySocket(proxySocket),
        thSend(clientEvents, proxySocket),
        thRecv(serverEvents,proxySocket),
        gui(SCREEN_WIDTH, SCREEN_HEIGHT, clientEvents){

    /*Lanzo los threads*/
    thSend.start();
    thRecv.start();
}

int Client::run() {
    this->init();

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;

    gui.addRenderable(200, 200, "arania1");
    gui.addRenderable(200, 300, "arania1");
    gui.addRenderable(300, 200, "esqueleto12");
    gui.addRenderable(400, 200, "zombie99");
    gui.addRenderable(500, 200, "goblin1");
    gui.addRenderable(500, 300, "juancito");

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
                        std::vector<std::string> player_inventory{"sword", "16000", "button"};
                        gui.update(std::move(player_inventory));
                        std::random_device rd;
                        std::mt19937 mt(rd());
                        std::uniform_real_distribution<float> dist(0.1,1.0);
                        t_stats stats{dist(mt),dist(mt),dist(mt),1000,50};
                        gui.update(stats);
                    }
                    break;
            }
            gui.handleEvents(event);
        }
        /*Logic*/
        gui.execute();

        /*Consumo la lista de eventos del server y actualizo modelo*/
        this->update();

        //Render objects
        gui.render();

        //Cap FPS 50
        SDL_Delay(20);
    }
    return 0;
}

void Client::init() {
    /*Me conecto al server*/
    //clientEvents.push(std::unique_ptr<Message>(new Connect("agus")));
    int init = 0;
    /*Consumo la lista hasta recibir DOS mensaje draw*/
    while(init < 2){
        std::cout << "client: consuming" << std::endl;
        std::list<std::unique_ptr<Message>> messages = this->serverEvents.consume();
        for (auto & msg : messages) {
            std::cout << msg->getId() << std::endl;
            if(msg->getId() == DRAW_MESSAGE_ID){
                init += 1;
                std::vector<int> data = msg->getData();
                for(unsigned long i = 0; i < data.size(); i++){
                    int x = i % msg->getWidth();
                    int y = i / msg->getHeight();
                    int id = data[i];
                    if(id != 0){
                        //this->gui.addTile(x, y, id);
                        if(init == 1) this->gui.addFloorTile(x, y, id);
                        else this->gui.addObstacleTile(x, y, id);
                    }
                }
            } else if(msg->getId() == INVENTORY_UPDATE_MESSAGE_ID) {
                 this->gui.update(msg->getItems());
            } else if(msg->getId() == STATS_UPDATE_MESSAGE_ID) {
                 this->gui.update(msg->getStats());
            }
        }
    }
}

void Client::update() {
    std::list<std::unique_ptr<Message>> messages = this->serverEvents.consume();
    /**TODO: Factory de eventos de server ????*/
    for(auto & msg : messages){
        if(msg->getId() == MOVEMENT_MESSAGE_ID){
            this->gui.update(msg->getPlayerVelX(), msg->getPlayerVelY());
        } else if(msg->getId() == STATS_UPDATE_MESSAGE_ID){
            this->gui.update(msg->getStats());
        } else if (msg->getId() == INVENTORY_UPDATE_MESSAGE_ID){
            this->gui.update(msg->getItems());
        }
    }
}

void Client::stop() {
    thSend.stop();
    thRecv.stop();
    thSend.join();
    thRecv.join();
}

Client::~Client() {
}

