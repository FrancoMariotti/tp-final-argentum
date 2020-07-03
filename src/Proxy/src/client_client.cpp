//
// Created by agustin on 13/6/20.
//

#include <thread>
#include <random>
#include "client_client.h"
#include "common_message.h"
#include "client_protected_list.h"
#include "client_sdl_chunk.h"
#include "client_sdl_music.h"

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
                        std::vector<std::string> player_inventory{"sword","axe","hammer","fresnoWand"
                                ,"crimpStick","commonBow", "rareBow"
                                ,"leatherArmour", "ironArmour", "blueTunic",
                                                                  "hood", "ironHelmet", "turtleShell", "ironShield",
                                                                  "magicHat", "smallLifePotion", "smallManaPotion"};
                        gui.updateInventory(std::move(player_inventory));
                        std::random_device rd;
                        std::mt19937 mt(rd());
                        std::uniform_real_distribution<float> dist(0.1,1.0);
                        t_stats stats{dist(mt),dist(mt),dist(mt),1000,50};
                        gui.updatePlayerStats(stats);
                        //std::vector<std::string> drops{"sword","axe"};
                        //gui.updateDrops(drops);
                    } else if (event.key.keysym.sym == SDLK_o){
                 //       testChunk.play(0);
                    } else if (event.key.keysym.sym == SDLK_i) {
                   //     testMusic.play(0);
                    } else if (event.key.keysym.sym == SDLK_p){
                     //       testMusic.stop();
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
    //clientEvents.push(std::unique_ptr<Message>(new Connect("franco","human,"wizard")));
    int init = 0;
    /*Consumo la lista hasta recibir DOS mensaje draw*/
    while(init < 2){
        //std::cout << "client: consuming" << std::endl;
        std::list<std::unique_ptr<Message>> messages = this->serverEvents.consume();
        for (auto & msg : messages) {
            std::cout << msg->getId() << std::endl;
            if(msg->getId() == DRAW_MESSAGE_ID){
                init += 1;
                std::vector<int> data = msg->getData();
                this->gui.setWorldDimensions(msg->getWidth(), msg->getHeight());
                this->gui.addWorldLayer(std::move(data), init);
            } else if(msg->getId() == INVENTORY_UPDATE_MESSAGE_ID) {
                this->gui.updateInventory(msg->getItems());
            } else if(msg->getId() == STATS_UPDATE_MESSAGE_ID) {
                this->gui.updatePlayerStats(msg->getStats());
            } else if (msg->getId() == SPAWN_NPC_MESSAGE_ID){
                this->gui.updateRenderables(msg->getSpawnData());
            } else if (msg->getId() == EQUIPMENT_UPDATE_MESSAGE_ID){
                gui.updatePlayerEquipment(msg->getEquipment());
            }
        }
    }
}

void Client::update() {
    std::list<std::unique_ptr<Message>> messages = this->serverEvents.consume();
    /**TODO: Factory de eventos de server ????*/
    for(auto & msg : messages){
        if(msg->getId() == MOVEMENT_MESSAGE_ID){
            this->gui.updatePlayerPos(msg->getPlayerVelX(), msg->getPlayerVelY());
        } else if(msg->getId() == STATS_UPDATE_MESSAGE_ID){
            this->gui.updatePlayerStats(msg->getStats());
        } else if (msg->getId() == INVENTORY_UPDATE_MESSAGE_ID){
            this->gui.updateInventory(msg->getItems());
        } else if (msg->getId() == SPAWN_NPC_MESSAGE_ID){
            this->gui.updateRenderables(msg->getSpawnData());
        } else if(msg->getId() == NPC_MOVEMENT_UPDATE_MESSAGE_ID){
            npc_movement_t  movement = msg->getMovement();
            this->gui.updateRenderablePos(movement.x, movement.y, movement.id);
        } else if (msg->getId() == EQUIPMENT_UPDATE_MESSAGE_ID){
            gui.updatePlayerEquipment(msg->getEquipment());
        }
    }
}

void Client::stop() {
    thSend.stop();
    thRecv.stop();
    thSend.join();
    thRecv.join();
}

Client::~Client() = default;

