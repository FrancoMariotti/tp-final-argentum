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

class SdlConsole;
class SdlInventory;
class SdlMouse;
class EventMediator : public IMediator{
private:
    BlockingQueue<std::unique_ptr<Message>> &clientEvents;
    SdlMouse& mouse;
    SdlInventory& inventory;
    SdlConsole& console;
    //ConsoleCommandState commandState;
public:
    EventMediator(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlMouse &mouse, SdlInventory &inventory,
                  SdlConsole &console);

    void notify(BaseComponent* sender, SDL_Point right_click ) override;

    void notify(BaseComponent* component) override;

    void notify(SdlConsole *console, std::string &s_input) override;
};


#endif //ARGENTUM_CLIENT_EVENT_MEDIATOR_H
