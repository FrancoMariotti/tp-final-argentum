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

class EventMediator : public IMediator{
private:
    BlockingQueue<std::unique_ptr<Message>> &clientEvents;
    SdlRenderablePlayable& player;
    BaseComponent& mouse;
public:
    explicit EventMediator(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlRenderablePlayable &player,
                           BaseComponent &mouse);

    void notify(BaseComponent* sender, SDL_Point right_click ) override;
};


#endif //ARGENTUM_CLIENT_EVENT_MEDIATOR_H
