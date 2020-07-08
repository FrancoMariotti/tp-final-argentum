//
// Created by agustin on 6/7/20.
//

#ifndef ARGENTUM_CLIENT_EVENT_MEDIATOR_H
#define ARGENTUM_CLIENT_EVENT_MEDIATOR_H


#include <memory>
#include "client_imediator.h"
#include "common_message.h"
#include "common_blocking_queue.h"
#include "client_sdl_dynamic_renderable.h"

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
    IConsoleCommandState* commandState;
    SDL_Point map_click;
    int inventory_item_index;
public:
    EventMediator(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlMouse &mouse, SdlInventory &inventory,
                  SdlConsole &console, const std::string &username);

    void notify(BaseComponent* sender, SDL_Point right_click ) override;

    void notify(BaseComponent* component) override;

    void notify(SdlConsole *console,const std::string &s_input) override;

    void notify(BaseComponent *sender, SDL_Point left_click, int overload) override;

    void notify(BaseComponent *sender, int i) override;

    void setMapClick(SDL_Point new_map_click);

    void changeState(IConsoleCommandState* newState);

    SDL_Point getMapClick();

    ~EventMediator();

    int getItemIndex() const;

    void setInventoryIndex(int inventory_i);
};


#endif //ARGENTUM_CLIENT_EVENT_MEDIATOR_H
