//
// Created by agustin on 13/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_INVENTORY_H
#define ARGENTUM_CLIENT_SDL_INVENTORY_H


#include "client_sdl_button.h"
#include "client_sdl_player.h"
#include "client_sdl_mouse.h"
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
    const int BUTTON_SIZE = 40;
    const std::vector<std::string> GAME_ITEMS_ID{"sword","axe","hammer","fresnoWand"
            ,"crimpStick","commonBow", "rareBow"
            ,"leatherArmour", "ironArmour", "blueTunic",
            "hood", "ironHelmet", "turtleShell", "ironShield",
            "magicHat", "smallLifePotion", "smallManaPotion"};

    const SdlWindow& window;

    //Una lista con todos los items del inventario, son botones
    std::vector<SdlButton> buttons;
    //Un map con todas las texturas de los items del inventario
    std::map<std::string, SdlTexture> inventoryTextures;

public:
    SdlInventory(int screen_width, int screen_height, const SdlWindow &window);

    void handleEvent(SDL_Event &event, bool &is_event_handled);

    void use(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlMouse &mouse);

    void update(std::vector<std::string> inventory);

    void render();

    ~SdlInventory();

    void renderDrop(const int x, const int y, const std::string &id);
};


#endif //ARGENTUM_CLIENT_SDL_INVENTORY_H
