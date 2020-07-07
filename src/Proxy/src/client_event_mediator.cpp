//
// Created by agustin on 6/7/20.
//

#include "client_event_mediator.h"
#include "client_sdl_button.h"
#include "client_sdl_inventory.h"

EventMediator::EventMediator(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlMouse &mouse,
                             SdlInventory &inventory,
                             SdlConsole &console) :
    clientEvents(clientEvents),
    mouse(mouse),
    inventory(inventory),
    console(console){
        mouse.setMediator(this);
        inventory.setMediator(this);
}

void EventMediator::notify(BaseComponent* sender, SDL_Point right_click) {
    //std::string username = player.getUsername();
    clientEvents.push(std::unique_ptr <Message>(new Attack("franco",
                   right_click.x, right_click.y)));
}

void EventMediator::notify(BaseComponent *component) {
    inventory.unlockOutlineSprite();
}

void EventMediator::notify(SdlConsole *sender, std::string& s_input) {

}


