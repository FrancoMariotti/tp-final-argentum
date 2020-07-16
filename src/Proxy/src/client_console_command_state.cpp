//
// Created by agustin on 7/7/20.
//

#include "client_console_command_state.h"

IConsoleCommandState::IConsoleCommandState(EventMediator *eventMediator) :
    eventMediator(eventMediator)
    {}

WaitingState::WaitingState(EventMediator* eventMediator) :
    IConsoleCommandState(eventMediator)
    {
    std::cout << "WaitingState" << std::endl;
    }

void WaitingState::setMapClick(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SDL_Point map_click) {
    eventMediator->setMapClick(map_click);
    eventMediator->changeState(new MapClickedState(eventMediator));
}

void WaitingState::execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, const std::string &s_input) {
    if (s_input == "/meditar" || s_input == "/resucitar" || s_input == "/tomar" || s_input.find('@') == 0) {
        clientEvents.push(std::unique_ptr<Message>
                                  (new ExecuteCommand(s_input, eventMediator->getUsername())));
    }
}

void WaitingState::setInventoryIndex(int inventory_i) {
    eventMediator->setInventoryIndex(inventory_i);
    eventMediator->changeState(new ItemClickedState(eventMediator));
}

/*Map clicked*/
MapClickedState::MapClickedState(EventMediator* eventMediator) :
    IConsoleCommandState(eventMediator)
    {
        std::cout << "MapClickedState" << std::endl;

    }

void MapClickedState::setMapClick(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SDL_Point map_click) {
    eventMediator->setMapClick(map_click);
}

/**Tal vez seria mejor delegarlo al eventMediator->pushEvent(input,x,y)
 * asi el state no conoce de los mensajes o al reves, que solo los State conozcan de los mensajes*/
void MapClickedState::execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, const std::string &s_input) {
    if (s_input == "/resucitar" || s_input == "/curar" || s_input == "/depositar" || s_input == "/listar" ) {
        SDL_Point map_click = eventMediator->getMapClick();
        clientEvents.push(std::unique_ptr<Message>
                (new ExecuteCommand(s_input, eventMediator->getUsername(), map_click.x, map_click.y)));
    } else if(s_input.find("/depositar") == 0 || s_input.find("/retirar") == 0 ||
    s_input.find("/comprar") == 0 || s_input.find("/vender") == 0 ){
        SDL_Point map_click = eventMediator->getMapClick();
        clientEvents.push(std::unique_ptr<Message>
                                  (new ExecuteCommand(s_input, eventMediator->getUsername(), map_click.x, map_click.y)));
    }
    eventMediator->changeState(new WaitingState(eventMediator));
}

void MapClickedState::setInventoryIndex(int inventory_i) {
    eventMediator->setInventoryIndex(inventory_i);
    eventMediator->changeState(new ItemClickedState(eventMediator));
}

/*Item clicked*/
ItemClickedState::ItemClickedState(EventMediator *eventMediator) :
    IConsoleCommandState(eventMediator)
    {}

void ItemClickedState::setMapClick(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SDL_Point map_click) {
    eventMediator->setMapClick(map_click);
    eventMediator->changeState(new MapClickedState(eventMediator));
}

void ItemClickedState::execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, const std::string &s_input) {
    if (s_input == "/tirar"){
        int index = eventMediator->getItemIndex();
        clientEvents.push(std::unique_ptr<Message>
                                  (new ExecuteCommand(s_input, eventMediator->getUsername(), index, 0)));
    }
    eventMediator->changeState(new WaitingState(eventMediator));
}

void ItemClickedState::setInventoryIndex(int inventory_i) {
    eventMediator->setInventoryIndex(inventory_i);
}
