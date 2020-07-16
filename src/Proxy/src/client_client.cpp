#include <thread>
#include <random>
#include "client_client.h"
#include "Common/Message.h"
#include "client_protected_list.h"

//Screen dimension constants
#define SCREEN_WIDTH 1024//640
#define SCREEN_HEIGHT 768//480

Client::Client(const std::string& hostname, const std::string& service):thSend(clientEvents, socket),
                                                                        thRecv(serverEvents,socket),
                                                                        gui(SCREEN_WIDTH, SCREEN_HEIGHT, clientEvents) {
    socket.connect(hostname.c_str(),service.c_str());
    /*Lanzo los threads*/
    thSend.start();
    thRecv.start();
}


/*Client::Client(ProxySocket& proxySocket) :
        proxySocket(proxySocket),
        thSend(clientEvents, proxySocket),
        thRecv(serverEvents,proxySocket),
        gui(SCREEN_WIDTH, SCREEN_HEIGHT, clientEvents){

    Lanzo los threads
    thSend.start();
    thRecv.start();
}*/

int Client::run() {
    try{

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
                    case SDL_KEYDOWN:
                        if(event.key.keysym.sym == SDLK_h){
                            gui.updateRenderableStats("franco", "explosion");
                        }
                        if(event.key.keysym.sym == SDLK_j){
                            gui.updateRenderableStats("franco", "missile");
                        }
                        if(event.key.keysym.sym == SDLK_k){
                            gui.updateRenderableStats("franco", "magicArrow");
                        }
                        if(event.key.keysym.sym == SDLK_l){
                            gui.updateRenderableStats("franco", "heal");
                        }
                        if(event.key.keysym.sym == SDLK_g){
                            gui.updateRenderableStats("franco", "meditate");
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
    } catch (std::exception & e){
        std::cout << e.what() << std::endl;
        return 1;
    } catch (...){
        std::cout << "Unknow error" << std::endl;
        return 1;
    }

    return 0;
}

void Client::init() {
    std::string username_input;
    std::cout << "Ingrese el nombre del jugador" << std::endl;
    std::cin >> username_input;

    clientEvents.push(std::unique_ptr<Message>(new Connect(username_input,"human","wizard")));
    gui.setUsername(username_input);
    int init = 0;
    /*Consumo la lista hasta recibir DOS mensaje draw y un SPAWN_PC*/
    while(init < 3){
        std::list<std::unique_ptr<Message>> messages = this->serverEvents.consume();
        for (auto & msg : messages) {
            std::cout << "init():Message ID: " << msg->getId() << std::endl;
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
                equipment_t equipment = msg->getEquipment();
                gui.updateRenderablePlayableEquipment(equipment,equipment.username);
                //gui.updatePlayerEquipment(equipment);
            } else if (msg->getId() == SPAWN_CITY_CHARACTERS_MESSAGE_ID) {
                gui.initStaticRenderables(msg->getSpawnData());
            } else if (msg->getId() == MOVEMENT_MESSAGE_ID) {
                location_t location = msg->getLocation();
                this->gui.updatePlayerPos(location.id,location.x, location.y);
            } else if (msg->getId() == SPAWN_DROPS_MESSAGE_ID) {
                this->gui.updateDrops(msg->getSpawnData());
            } else if (msg->getId() == SPAWN_PC_MESSAGE_ID) {
                /*Agregue este init extra para asegurar que haya spawneado el player*/
                init += 1;
                gui.updateRenderablePlayables(msg->getPcSpawnData());
            }
        }
    }
    std::cout << "end of init()" << std::endl;
}

void Client::update() {
    std::list<std::unique_ptr<Message>> messages = this->serverEvents.consume();
    /**TODO: Factory de eventos de server ????*/
    for(auto & msg : messages){
        //std::cout << "Update(): MessageId" << msg->getId() << std::endl;
        if(msg->getId() == MOVEMENT_MESSAGE_ID){
            location_t  location = msg->getLocation();
            this->gui.updatePlayerPos(location.id,location.x, location.y);
        } else if(msg->getId() == STATS_UPDATE_MESSAGE_ID){
            this->gui.updatePlayerStats(msg->getStats());
        } else if (msg->getId() == INVENTORY_UPDATE_MESSAGE_ID){
            this->gui.updateInventory(msg->getItems());
        } else if (msg->getId() == SPAWN_NPC_MESSAGE_ID){
            this->gui.updateRenderables(msg->getSpawnData());
        } else if (msg->getId() == SPAWN_DROPS_MESSAGE_ID) {
            this->gui.updateDrops(msg->getSpawnData());
        } else if(msg->getId() == NPC_MOVEMENT_UPDATE_MESSAGE_ID){
            location_t  movement = msg->getLocation();
            this->gui.updateRenderablePos(movement.x, movement.y, movement.id);
        } else if (msg->getId() == EQUIPMENT_UPDATE_MESSAGE_ID){
            equipment_t equipment = msg->getEquipment();
            gui.updateRenderablePlayableEquipment(equipment,equipment.username);
            //gui.updatePlayerEquipment(equipment);
        } else if (msg->getId() == CONSOLE_OUTPUT_MESSAGE_ID){
            gui.updateConsoleOutput(msg->getConsoleOutput());
        } else if (msg->getId() == SPAWN_PC_MESSAGE_ID) {
            gui.updateRenderablePlayables(msg->getPcSpawnData());
        }
        /*else if (msg->getId() == RENDERABLE_EFFECT_MESSAGE_ID){
           gui.updateRenderableStats(msg->getRenderableId(), msg->getEffectId());
        }*/
    }
}

void Client::stop() {
    thSend.stop();
    thRecv.stop();
    thSend.join();
    thRecv.join();
}

Client::~Client() = default;

