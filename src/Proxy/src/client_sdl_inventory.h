//
// Created by agustin on 13/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_INVENTORY_H
#define ARGENTUM_CLIENT_SDL_INVENTORY_H


#include "client_sdl_button.h"
#include <vector>
#include <map>

class Message;
class SdlInventory {
private:
    /*Tamaño del inventario*/
    int width;
    int height;
    /*Posicion del inventario*/
    int inventory_x;
    int inventory_y;
    int button_size;

    const SdlWindow& window;

    //Una lista con todos los items del inventario, son botones
    std::vector<SdlButton*> buttons;
    //Un map con todas las texturas de los items del inventario
    std::map<std::string, SdlTexture> inventoryTextures;

public:
    SdlInventory(int screen_width, int screen_height, const SdlWindow &window);

    void handleEvents(SDL_Event &event);

    /*logic*/
    void use(BlockingQueue<std::unique_ptr<Message>> &clientEvents);

    void render();

    ~SdlInventory();

    void addItem(const std::string &item_id);
};


#endif //ARGENTUM_CLIENT_SDL_INVENTORY_H
