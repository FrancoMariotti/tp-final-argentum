//
// Created by agustin on 13/6/20.
//

#include <zconf.h>
#include "client_client.h"

Client::Client() :
    window(SCREEN_WIDTH, SCREEN_HEIGHT),
    background(SCREEN_WIDTH, SCREEN_HEIGHT, "../../Proxy/assets/dungeon.png", window)
    {
    //Permito la carga del PNGs
    window.initPNG();
}

int Client::run() {
    //Cargo al personaje
    SdlTexture head_sprite_sheet(17,15,"../../Proxy/assets/2005.gif", window);
    SdlTexture texture("../../Proxy/assets/340.gif", window);

    //Botones
    std::vector<SdlButton*> buttons;
    SdlTexture buttonSpriteSheet(100,100,"../../Proxy/assets/button.png", window);
    for (int i = 0; i < 3 ; ++i) {
        Command* cmd = new Equip();
        /*Alojo los botones en el heap dado el parametro new Command*/
        buttons.push_back(new SdlButton(buttonSpriteSheet, cmd));
        buttons.back()->setPosition(SCREEN_WIDTH - (buttonSpriteSheet.getWidth()),
                                    buttonSpriteSheet.getHeight() * i);
    }
    Command* cmd = new Move();
    buttons.push_back(new SdlButton(buttonSpriteSheet, cmd));
    buttons.back()->setPosition(SCREEN_WIDTH - (2*buttonSpriteSheet.getWidth()), 0);

    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event event;

    SdlPlayer player(100, 100, texture, head_sprite_sheet);

    //While application is running
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&event) != 0) {
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    player.handleEvent(event, proxySocket);

                    /*Proxy respuesta del server*/
                    t_command movement = proxySocket.readClient();
                    player.move(movement);
                    break;
            }
        }
        //Handle de los botones
        for(auto & button : buttons){
            button->handleEvent(&event, proxySocket);
        }

        //Renderizo background
        background.render(0,0);
        //Render objects
        player.render();
        //Renderizo botones
        for (auto & button : buttons) {
            button->render();
        }
        //Update screen
        window.render();
    }

    //delete buttons
    for(auto & button : buttons){
        delete button;
    }

    //Close SDL
    this->close();


}


void Client::close(){
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
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

