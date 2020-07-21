//
// Created by agustin on 13/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_INVENTORY_H
#define ARGENTUM_CLIENT_SDL_INVENTORY_H


#include "client_sdl_button.h"
#include "client_sdl_mouse.h"
#include "Common/Messages/message_structs.h"
#include "client_event_mediator.h"
#include <vector>
#include <map>

class Message;
class SdlInventory : public BaseComponent {
private:
    /*Tamaño del inventario*/
    int width;
    int height;

    /*Posicion del inventario*/
    int inventory_x;
    int inventory_y;
    const int BUTTON_SIZE = 32;
    const int MAX_BUTTONS_PER_ROW;
    const std::vector<std::string> GAME_ITEMS_ID{"sword","axe","hammer","fresnoWand"
            ,"crimpStick","knottyStick","elvenFlute","commonBow", "rareBow","defaultArmour"
            ,"leatherArmour", "ironArmour", "blueTunic",
            "hood", "ironHelmet", "turtleShell", "ironShield",
            "magicHat", "smallLifePotion", "smallManaPotion",
            "bigLifePotion", "bigManaPotion", "goldBag"};

    const SdlWindow& window;
    TTF_Font* font;

    //Una lista con todos los items del inventario, son botones
    std::vector<SdlButton> buttons;
    //Un map con todas las texturas de los items del inventario
    std::map<std::string, SdlTexture> inventoryTextures;

    std::vector<int> equipped_items_indexes;

public:
    SdlInventory(const SdlWindow &window, TTF_Font *font);

    void handleEvent(SDL_Event &event, bool &is_event_handled);

    void use(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlMouse &mouse);

    /*Actualiza la posicion de los items en el inventario*/
    void update(std::vector<std::string> inventory);

    /*Renderiza el inventario y todos los items*/
    void render();

    /*Renderiza en la posicion indica el item con el @param id*/
    /**No deberia ser responsabilidad del inventario*/
    void renderDrop(const int x, const int y, const std::string &id);

    void updateEquippedItems(const equipment_t &equipment);

    void unlockOutlineSprite();

    void notify(int inventory_i);

    ~SdlInventory();
};


#endif //ARGENTUM_CLIENT_SDL_INVENTORY_H
