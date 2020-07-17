//
// Created by agustin on 13/6/20.
//

#include "client_sdl_inventory.h"
#include "client_sdl_player.h"
#include "client_sdl_window.h"
#include "Common/message_structs.h"
#include "client_sdl_text.h"

/*Estos tamaños son con 1024 x 768*/
#define IMAGE_INVENTORY_WIDTH 165
#define IMAGE_INVENTORY_HEIGHT 308
#define INVENTORY_X 820
#define INVENTORY_Y 180


SdlInventory::SdlInventory(const SdlWindow &window, TTF_Font *font) :
        width(IMAGE_INVENTORY_WIDTH),
        height(IMAGE_INVENTORY_HEIGHT),
        MAX_BUTTONS_PER_ROW(width / BUTTON_SIZE),
        window(window),
        font(font)
        {

    //inicializo la posicion del inventario
    this->inventory_x = INVENTORY_X; //window.getWidth * 0.8 ;
    this->inventory_y = INVENTORY_Y; //screen_height * 0.234;

    for(auto it = GAME_ITEMS_ID.begin(); it != GAME_ITEMS_ID.end(); ++it){
        inventoryTextures.emplace(std::piecewise_construct,
                std::forward_as_tuple(*it),
                std::forward_as_tuple(BUTTON_SIZE, BUTTON_SIZE, "../../Proxy/items/" + *it +".png", window)
        );
    }
    inventoryTextures.emplace(std::make_pair("outline", SdlTexture(BUTTON_SIZE,
            BUTTON_SIZE,
            "../../Proxy/assets/1.png" ,window)));
}

void SdlInventory::handleEvent(SDL_Event &event, bool &is_event_handled) {
    int x,y;
    SDL_GetMouseState(&x,&y);
    is_event_handled = (x > inventory_x && x < inventory_x + width && y > inventory_y && y < inventory_y + height);
    for(auto & button : buttons){
        button.handleEvent(event, is_event_handled);
    }
}

void SdlInventory::use(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlMouse &mouse) {
    for (unsigned long i = 0; i < buttons.size() ; ++i) {
        /*Veo si fueron clickeados*/
        buttons[i].use(clientEvents, (int) i, mouse, this);
    }
}

void SdlInventory::unlockOutlineSprite(){
    for(auto & button : buttons){
        button.lockOutlineSprite(false);
    }
}

void SdlInventory::update(std::vector<std::string> inventory) {
    buttons.clear();
    SdlTexture& outline = inventoryTextures.at("outline");
    for(auto it = inventory.begin(); it != inventory.end(); it ++){
        SdlTexture& buttonSpriteSheet = inventoryTextures.at(*it);
        int col = (int) buttons.size() % MAX_BUTTONS_PER_ROW;
        int fil = (int) buttons.size() / MAX_BUTTONS_PER_ROW;
        buttons.emplace_back(buttonSpriteSheet, outline, font, window, *it);
        /*Seteo la posicion relativa al inventario,
         * a medida que pusheo se van acomodando uno al lado del otro*/
        /*4 botones por fila,
         * 0....3
         * 4....7*/
        buttons.back().setPosition(inventory_x + col * BUTTON_SIZE,
                                       inventory_y + fil * BUTTON_SIZE);
    }
}


void SdlInventory::updateEquippedItems(const equipment_t &equipment) {
    for(auto it = buttons.begin(); it != buttons.end(); it ++){
        it->updateText(equipment);
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

void SdlInventory::renderDrop(const int x, const int y,const std::string& id){
    this->inventoryTextures.at(id).render(x,y);
}

void SdlInventory::notify(int inventory_i) {
    mediator->notify(this, inventory_i);
}

SdlInventory::~SdlInventory() {
}

