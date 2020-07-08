//
// Created by agustin on 7/7/20.
//

#include "client_console_command_state.h"

IConsoleCommandState::IConsoleCommandState(EventMediator *eventMediator) :
    eventMediator(eventMediator)
    {}

WaitingState::WaitingState(EventMediator* eventMediator) :
    IConsoleCommandState(eventMediator)
    {}

void WaitingState::setMapClick(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SDL_Point map_click) {
    eventMediator->setMapClick(map_click);
    eventMediator->changeState(new MapClickedState(eventMediator));
}

void WaitingState::execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, const std::string &s_input) {
}


MapClickedState::MapClickedState(EventMediator* eventMediator) :
    IConsoleCommandState(eventMediator)
    {}

void MapClickedState::setMapClick(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SDL_Point map_click) {

}

void MapClickedState::execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, const std::string &s_input) {
    if (s_input == ("/listar")) {
        SDL_Point map_click = eventMediator->getMapClick();
        clientEvents.push(
                std::unique_ptr<Message>(new ExecuteCommand(s_input,
                        map_click.x, map_click.y)));
    }
    eventMediator->changeState(new WaitingState(eventMediator));

}
