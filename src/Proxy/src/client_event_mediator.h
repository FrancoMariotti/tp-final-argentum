//
// Created by agustin on 6/7/20.
//

#ifndef ARGENTUM_CLIENT_EVENT_MEDIATOR_H
#define ARGENTUM_CLIENT_EVENT_MEDIATOR_H


#include <memory>
#include "client_imediator.h"
#include "Common/Messages/Message.h"
#include "Common/BlockingQueue.h"
#include "client_sdl_dynamic_renderable.h"

class SdlKeyboard;
class IConsoleCommandState;
class SdlConsole;
class SdlInventory;
class SdlMouse;
class EventMediator : public IMediator{
private:
    const std::string& USERNAME;
    BlockingQueue<std::unique_ptr<Message>> &clientEvents;
    SdlMouse& mouse;
    SdlInventory& inventory;
    SdlConsole& console;
    SdlKeyboard& keyboard;
    IConsoleCommandState* commandState;
    SDL_Point map_click;
    int inventory_item_index;
public:
    EventMediator(const std::string &username, BlockingQueue<std::unique_ptr<Message>> &clientEvents,
                  SdlMouse &mouse, SdlInventory &inventory, SdlConsole &console, SdlKeyboard &keyboard);

    /*Notifica cuando hubo un click derecho en el mapa*/
    void notify(BaseComponent* sender, SDL_Point right_click ) override;

    /*Remueve el marco de seleccion de todos los items del inventario*/
    void notify(BaseComponent* component) override;

    /*Delega la ejecucion del comando*/
    void notify(SdlConsole *console,const std::string &s_input) override;

    void notify(BaseComponent *sender, SDL_Point left_click, int overload) override;

    void notify(BaseComponent *sender, int i) override;

    /*Encola el evento movimiento del jugador*/
    void notify(BaseComponent *sender, int vel_x, int vel_y) override;

    void setMapClick(SDL_Point new_map_click);

    void changeState(IConsoleCommandState* newState);

    SDL_Point getMapClick();

    const std::string& getUsername() const;

    int getItemIndex() const;

    void setInventoryIndex(int inventory_i);

    ~EventMediator();
};


#endif //ARGENTUM_CLIENT_EVENT_MEDIATOR_H
