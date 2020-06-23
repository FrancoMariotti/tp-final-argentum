//
// Created by agustin on 13/6/20.
//

#include "client_sdl_inventory.h"
#include "client_sdl_player.h"
#include "client_sdl_window.h"

/*Estos tamaños son con 1024 x 768*/
#define IMAGE_INVENTORY_WIDTH 165
#define IMAGE_INVENTORY_HEIGHT 308
#define INVENTORY_X 820
#define INVENTORY_Y 180


SdlInventory::SdlInventory(int screen_width, int screen_height, const SdlWindow &window, SdlPlayer &player) :
    x_from_player(INVENTORY_X - (screen_width / 2)),
    y_from_player((screen_height / 2) - INVENTORY_Y),
    window(window),
    player(player){
    //Tamaño ventana inventario
    this->width = IMAGE_INVENTORY_WIDTH;
    this->height = IMAGE_INVENTORY_HEIGHT;

    //inicializo la posicion del inventario
    this->inventory_x = player.getPosX() + x_from_player;
    this->inventory_y = player.getPosY() - y_from_player;

    this->button_size = 40;

    //Botones
    inventoryTextures.emplace(std::piecewise_construct,
            std::forward_as_tuple("button"),
            std::forward_as_tuple(button_size,button_size,"../../Proxy/assets/button.png", window)
            );
    SdlTexture& buttonSpriteSheet = inventoryTextures.at("button");

    /*Prueba, esto deberia ser un handler cuando el jugador agrega items al inventario*/
    for (int i = 0; i < 5 ; ++i) {
        int col = (int) buttons.size() % 4;
        int fil = (int) buttons.size() / 4;
        Command* cmd = new Use;
        /*Alojo los botones en el heap dado el parametro new Command*/
        buttons.push_back(new SdlButton(buttonSpriteSheet, cmd));
        /*Seteo la posicion relativa al inventario,
         * a medida que pusheo se van acomodando uno al lado del otro*/
        /*4 botones por fila,
         * 0....3
         * 4....7*/
        buttons.back()->setPosition(inventory_x + col * button_size,
                                    inventory_y + fil * button_size);
    }

}

void SdlInventory::handleEvents(SDL_Event &event) {
    /*Client side events*/
    for(auto & button : buttons){
        button->handleEvent(event);
    }
}

void SdlInventory::use(BlockingQueue<std::unique_ptr<Message>>& clientEvents) {
    this->inventory_x = player.getPosX() + x_from_player;
    this->inventory_y = player.getPosY() - y_from_player;

    for (unsigned long i = 0; i < buttons.size() ; ++i) {
        /*Veo si fueron clickeados*/
        buttons[i]->use(clientEvents, (int) i);
        /*Actualizo la posicion de los botones*/
        int col = (int) i % 4;
        int fil = (int) i / 4;
        buttons[i]->setPosition(inventory_x + col * button_size,
                                inventory_y + fil * button_size);
    }
}

void SdlInventory::addItem(const std::string& item_id){
    /*El server me envia el id del item para cargarle la textura*/
    inventoryTextures.emplace(std::piecewise_construct,
                              std::forward_as_tuple(item_id),
                              std::forward_as_tuple(button_size,button_size,
                                      "../../Proxy/items/" + item_id + ".png", window)
    );
    SdlTexture& buttonTexture = inventoryTextures.at(item_id);
    int col = (int) buttons.size() % 4;
    int fil = (int) buttons.size() / 4;
    Command* cmd = new Use;
    buttons.push_back(new SdlButton(buttonTexture, cmd));
    buttons.back()->setPosition(inventory_x + col * button_size,
                                inventory_y + fil * button_size);
}

void SdlInventory::render() {
    SDL_Rect outline_rect = {inventory_x, inventory_y, width, height};
    SDL_SetRenderDrawColor(window.getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawRect(window.getRenderer(), &outline_rect);
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
