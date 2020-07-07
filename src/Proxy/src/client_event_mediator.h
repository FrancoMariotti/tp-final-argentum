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

class SdlInventory;
class SdlMouse;
class EventMediator : public IMediator{
private:
    BlockingQueue<std::unique_ptr<Message>> &clientEvents;
    SdlRenderablePlayable& player;
    SdlMouse& mouse;
    SdlInventory& inventory;
public:
     EventMediator(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlRenderablePlayable &player,
                   SdlMouse &mouse, SdlInventory &inventory);

    void notify(BaseComponent* sender, SDL_Point right_click ) override;

    void notify(BaseComponent* component) override;

};


#endif //ARGENTUM_CLIENT_EVENT_MEDIATOR_H
