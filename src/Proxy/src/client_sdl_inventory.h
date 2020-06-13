//
// Created by agustin on 13/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_INVENTORY_H
#define ARGENTUM_CLIENT_SDL_INVENTORY_H


#include "client_sdl_button.h"
#include <vector>
#include <map>

class SdlInventory {
private:
    /*Tamaño del inventario*/
    int width;
    int height;
    /*Posicion del inventario*/
    int inventory_x;
    int inventory_y;
    //Fondo del inventario
    SdlTexture inv_background;
    //Una lista con todos los items del inventario, son botones
    std::vector<SdlButton*> buttons;
    //Un map con todas las texturas de los items del inventario
    std::map<std::string, SdlTexture> inventoryTextures;

public:
    SdlInventory(int screen_width, int screen_height, const SdlWindow &window);

    void handleEvents(SDL_Event *event, ProxySocket &proxySocket);

    void render();

    ~SdlInventory();
};


#endif //ARGENTUM_CLIENT_SDL_INVENTORY_H