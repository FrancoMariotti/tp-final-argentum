//
// Created by agustin on 6/7/20.
//

#include "client_event_mediator.h"
#include "client_sdl_button.h"
#include "client_sdl_inventory.h"
#include "client_console_command_state.h"
#include "client_sdl_console.h"
#include "client_sdl_keyboard.h"

EventMediator::EventMediator(const std::string &username, BlockingQueue<std::unique_ptr<Message>> &clientEvents,
                             SdlMouse &mouse, SdlInventory &inventory, SdlConsole &console, SdlKeyboard &keyboard) :
    USERNAME(username),
    clientEvents(clientEvents),
    mouse(mouse),
    inventory(inventory),
    console(console),
    keyboard(keyboard),
    commandState(new WaitingState(this)),
    map_click{-1,-1},
    inventory_item_index(0){
        mouse.setMediator(this);
        inventory.setMediator(this);
        console.setMediator(this);
        keyboard.setMediator(this);
}


void EventMediator::notify(BaseComponent* sender, SDL_Point right_click) {
    clientEvents.push(std::unique_ptr <Message>(new ActionUpdate(PLAYER_ATTACK_MESSAGE_ID,USERNAME,
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


void EventMediator::notify(BaseComponent *sender, int i) {
    commandState->setInventoryIndex(i);
}


void EventMediator::notify(BaseComponent *sender, const int vel_x, const int vel_y) {
    clientEvents.push(std::unique_ptr<Message> (
            new Movement(vel_x, vel_y)));
}

void EventMediator::setMapClick(const SDL_Point new_map_click){
    map_click = new_map_click;
}

void EventMediator::setInventoryIndex(int inventory_i) {
    inventory_item_index = inventory_i;
}

SDL_Point EventMediator::getMapClick(){
    return map_click;
}

int EventMediator::getItemIndex() const {
    return inventory_item_index;
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


