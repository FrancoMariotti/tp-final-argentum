//
// Created by agustin on 13/6/20.
//

#include "client_sdl_inventory.h"

/*Estos tamaños son con 1024 x 768*/
#define IMAGE_INVENTORY_WIDTH 165
#define IMAGE_INVENTORY_HEIGHT 308
#define INVENTORY_X 820
#define INVENTORY_Y 180

/**TODO: Singleton?*/
#define SCREEN_RATIO 1

SdlInventory::SdlInventory(const int screen_width, const int screen_height, const SdlWindow &window) :
    window(window){
    //Tamaño ventana inventario
    this->width = IMAGE_INVENTORY_WIDTH * SCREEN_RATIO;
    this->height = IMAGE_INVENTORY_HEIGHT * SCREEN_RATIO;

    //Posicion (siempre a la derecha)
    this->inventory_x = INVENTORY_X * SCREEN_RATIO;
    this->inventory_y = INVENTORY_Y * SCREEN_RATIO;

    this->button_size = 40 * SCREEN_RATIO;

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
    /*Paso la posicion del inventario, i*/
    for (unsigned long i = 0; i < buttons.size() ; ++i) {
        buttons[i]->use(clientEvents, (int)i);
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
    //mainInterface.render(this->inventory_x,this->inventory_y);
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
