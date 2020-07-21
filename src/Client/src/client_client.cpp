#include <thread>
#include <random>
#include "client_client.h"
#include "Common/Messages/Message.h"
#include "client_protected_list.h"
#include "client_update_factory.h"

//Screen dimension constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

Client::Client(Socket &socket) :
    socket(socket),
    thSend(clientEvents, socket),
    thRecv(serverEvents,socket),
    gui(SCREEN_WIDTH, SCREEN_HEIGHT, clientEvents) {
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

int Client::run(const std::string &username) {
    try{
        gui.setUsername(username);

        UpdateFactory updateFactory;

        this->init(updateFactory);

        bool quit = false;

        SDL_Event event;
        SdlTimer capTimer;
        const int SCREEN_FPS = 30;
        const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

        while (!quit) {
            capTimer.start();
            while (SDL_PollEvent(&event) != 0) {
                switch(event.type){
                    case SDL_QUIT:
                        quit = true;
                        gui.disconnect();
                        break;
                }
                gui.handleEvents(event);
            }
            gui.execute();

            /*Consumo la lista de eventos del server y actualizo modelo*/
            this->update(updateFactory);

            gui.render();

            //Calculo los frames y espero lo restante para mantener los 60 FPS
            int frame_ticks = capTimer.getTicks();
            if(frame_ticks < SCREEN_TICKS_PER_FRAME){
                SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
            }
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

void Client::init(UpdateFactory &updateFactory) {
     int init = 0;
    /*Consumo la lista hasta recibir DOS mensaje draw y un SPAWN_PC*/
    while(init < 3){
        std::list<std::unique_ptr<Message>> messages = this->serverEvents.consume();
        for (auto & msg : messages) {
            if(msg->getId() == DRAW_MESSAGE_ID){
                init += 1;
                std::vector<int> data = msg->getData();
                this->gui.setWorldDimensions(msg->getWidth(), msg->getHeight());
                this->gui.addWorldLayer(std::move(data), init);
            } else if (msg->getId() == SPAWN_PC_MESSAGE_ID) {
                /*Me aseguro que haya spawneado el player*/
                init += 1;
                gui.updateRenderablePlayables(msg->getPcSpawnData());
            } else {
                const Update* up = updateFactory.getUpdate(msg->getId());
                up->execute(gui, std::move(msg));
            }
        }
    }
}

void Client::update(UpdateFactory &updateFactory) {
    std::list<std::unique_ptr<Message>> messages = this->serverEvents.consume();
    for(auto & msg : messages){
        const Update* up = updateFactory.getUpdate(msg->getId());
        up->execute(gui, std::move(msg));
    }
}

void Client::stop() {
    thSend.stop();
    thRecv.stop();
    thSend.join();
    thRecv.join();
}

Client::~Client() = default;
