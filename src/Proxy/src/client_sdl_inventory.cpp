//
// Created by agustin on 13/6/20.
//

#include "client_sdl_inventory.h"


SdlInventory::SdlInventory(const int screen_width, const int screen_height, const SdlWindow &window) :
    background(screen_width/3, screen_height, "../../Proxy/assets/background.png", window){
    //Tamaño ventana inventario
    this->width = screen_width / 3;
    this->height = screen_height;

    //Posicion (siempre a la derecha)
    this->inventory_x = screen_width - width;
    this->inventory_y = 0;

    //Botones
    inventoryTextures.emplace(std::piecewise_construct,
            std::forward_as_tuple("button"),
            std::forward_as_tuple(100,100,"../../Proxy/assets/button.png", window)
            );
    SdlTexture& buttonSpriteSheet = inventoryTextures.at("button");

    for (int i = 0; i < 3 ; ++i) {
        Command* cmd = new Equip();
        /*Alojo los botones en el heap dado el parametro new Command*/
        buttons.push_back(new SdlButton(buttonSpriteSheet, cmd));
        buttons.back()->setPosition(screen_width - (buttonSpriteSheet.getWidth()),
                                    buttonSpriteSheet.getHeight() * i);
    }
    Command* cmd = new Move();
    buttons.push_back(new SdlButton(buttonSpriteSheet, cmd));
    buttons.back()->setPosition(screen_width - (2 * buttonSpriteSheet.getWidth()), 0);

}

void SdlInventory::handleEvents(SDL_Event *event, ProxySocket &proxySocket) {
    for(auto & button : buttons){
        button->handleEvent(event, proxySocket);
    }
}

void SdlInventory::render() {
    background.render(this->inventory_x,this->inventory_y);
    for (auto & button : buttons) {
        button->render();
    }
}

SdlInventory::~SdlInventory() {
    //delete buttons
    for(auto & button : buttons){
        delete button;
    }
}
