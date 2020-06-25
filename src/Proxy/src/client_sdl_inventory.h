//
// Created by agustin on 13/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_INVENTORY_H
#define ARGENTUM_CLIENT_SDL_INVENTORY_H


#include "client_sdl_button.h"
#include "client_sdl_player.h"
#include <vector>
#include <map>

class Message;
class SdlInventory {
private:
    /*Tamaño del inventario*/
    int width;
    int height;
    /*Posicion del inventario*/
    const int X_FROM_PLAYER = 308;
    const int Y_FROM_PLAYER = 204;

    int inventory_x;
    int inventory_y;
    const int BUTTON_SIZE = 40;

    const SdlWindow& window;
    const SdlPlayer& player;

    //Una lista con todos los items del inventario, son botones
    std::vector<SdlButton*> buttons;
    //Un map con todas las texturas de los items del inventario
    std::map<std::string, SdlTexture> inventoryTextures;

public:
    SdlInventory(int screen_width, int screen_height, const SdlWindow &window, SdlPlayer &player);

    void handleEvents(SDL_Event &event, bool &is_event_handled);

    /*logic*/
    void use(BlockingQueue<std::unique_ptr<Message>> &clientEvents);

    void render();

    ~SdlInventory();

    void addItem(const std::string &item_id);

};


#endif //ARGENTUM_CLIENT_SDL_INVENTORY_H
