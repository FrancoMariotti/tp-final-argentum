//
// Created by agustin on 6/7/20.
//

#include "client_event_mediator.h"

EventMediator::EventMediator(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlRenderablePlayable &player,
                             BaseComponent &mouse) :
    clientEvents(clientEvents),
    player(player),
    mouse(mouse){
    mouse.setMediator(this);
}

void EventMediator::notify(BaseComponent* sender, SDL_Point right_click) {
    //std::string username = player.getUsername();
    clientEvents.push(std::unique_ptr <Message>(new Attack("franco",
                   right_click.x, right_click.y)));
}

