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


SdlInventory::SdlInventory(int screen_width, int screen_height, const SdlWindow &window) :
        window(window)
        {
    //Tamaño ventana inventario
    this->width = IMAGE_INVENTORY_WIDTH;
    this->height = IMAGE_INVENTORY_HEIGHT;

    //inicializo la posicion del inventario
    this->inventory_x = INVENTORY_X;
    this->inventory_y = INVENTORY_Y;

    for(auto it = GAME_ITEMS_ID.begin(); it != GAME_ITEMS_ID.end(); ++it){
        inventoryTextures.emplace(std::piecewise_construct,
                std::forward_as_tuple(*it),
                std::forward_as_tuple(BUTTON_SIZE, BUTTON_SIZE, "../../Proxy/items/" + *it +".png", window)
        );
    }


}

void SdlInventory::handleEvent(SDL_Event &event, bool &is_event_handled) {
    /*Client side events*/
    for(auto & button : buttons){
        button.handleEvent(event, is_event_handled);
    }
}

void SdlInventory::use(BlockingQueue<std::unique_ptr<Message>> &clientEvents) {
    for (unsigned long i = 0; i < buttons.size() ; ++i) {
        /*Veo si fueron clickeados*/
        buttons[i].use(clientEvents, (int) i);
    }
}

void SdlInventory::update(std::vector<std::string> inventory){
    buttons.clear();
    for(auto it = inventory.begin(); it != inventory.end(); it ++){
        SdlTexture& buttonSpriteSheet = inventoryTextures.at(*it);
        int col = (int) buttons.size() % 4;
        int fil = (int) buttons.size() / 4;
        buttons.emplace_back(buttonSpriteSheet);
        /*Seteo la posicion relativa al inventario,
         * a medida que pusheo se van acomodando uno al lado del otro*/
        /*4 botones por fila,
         * 0....3
         * 4....7*/
        buttons.back().setPosition(inventory_x + col * BUTTON_SIZE,
                                       inventory_y + fil * BUTTON_SIZE);

    }
}

void SdlInventory::render() {
    SDL_Rect outline_rect = {inventory_x, inventory_y, width, height};
    SDL_SetRenderDrawColor(window.getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderDrawRect(window.getRenderer(), &outline_rect);
    SDL_Rect background = {inventory_x, inventory_y, width, height};
    SDL_SetRenderDrawColor(window.getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(window.getRenderer(), &background);

    for (auto & button : buttons) {
        button.render();
    }
}

/*int SdlInventory::getLastClickedIndex(){

}*/

void SdlInventory::renderDrop(const int x, const int y,const std::string& id){
    this->inventoryTextures.at(id).render(x,y);
}

SdlInventory::~SdlInventory() {
}
