//
// Created by agustin on 6/7/20.
//

#include "client_event_mediator.h"
#include "client_sdl_button.h"
#include "client_sdl_inventory.h"
#include "client_console_command_state.h"
#include "client_sdl_console.h"

EventMediator::EventMediator(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SdlMouse &mouse,
                             SdlInventory &inventory,
                             SdlConsole &console) :
    clientEvents(clientEvents),
    mouse(mouse),
    inventory(inventory),
    console(console),
    commandState(new WaitingState(this)),
    map_click{-1,-1}{
        mouse.setMediator(this);
        inventory.setMediator(this);
        console.setMediator(this);
}


void EventMediator::notify(BaseComponent* sender, SDL_Point right_click) {
    //std::string username = player.getUsername();
    clientEvents.push(std::unique_ptr <Message>(new Attack("franco",
                   right_click.x, right_click.y)));
}

void EventMediator::notify(BaseComponent* sender, SDL_Point left_click, int overload) {
    this->commandState->setMapClick(clientEvents, left_click);
}


void EventMediator::notify(BaseComponent *component) {
    inventory.unlockOutlineSprite();
}


void EventMediator::notify(SdlConsole *sender, const std::string& s_input) {
    this->commandState->execute(clientEvents, s_input);
}


void EventMediator::setMapClick(const SDL_Point new_map_click){
    map_click = new_map_click;
}

SDL_Point EventMediator::getMapClick(){
    return map_click;
}

void EventMediator::changeState(IConsoleCommandState *newState) {
    if(this->commandState){
        delete commandState;
    }
    commandState = newState;
}

EventMediator::~EventMediator() {
    delete commandState;
}



