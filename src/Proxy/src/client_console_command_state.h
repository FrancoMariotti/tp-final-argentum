//
// Created by agustin on 7/7/20.
//

#ifndef ARGENTUM_CLIENT_CONSOLE_COMMAND_STATE_H
#define ARGENTUM_CLIENT_CONSOLE_COMMAND_STATE_H


#include <string>
#include "client_event_mediator.h"

class IConsoleCommandState {
protected:
    EventMediator* eventMediator;
    explicit IConsoleCommandState(EventMediator *eventMediator);
public:
    /*Guarda la posicion del mapa en la que se hizo click*/
    virtual void setMapClick(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SDL_Point map_click) const = 0;
    /*Setea el indice del item seleccionado*/
    virtual void setInventoryIndex(const int inventory_i) const = 0;
    virtual void execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, const std::string& s_input) const = 0;
    virtual ~IConsoleCommandState() = default;
};

class WaitingState : public IConsoleCommandState{
public:
    explicit WaitingState(EventMediator* eventMediator);
    void setMapClick(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SDL_Point map_click) const override;
    void setInventoryIndex(int inventory_i) const override;
    void execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, const std::string& s_input) const override;
};


class MapClickedState : public IConsoleCommandState{
public:
    explicit MapClickedState(EventMediator* eventMediator);
    void setMapClick(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SDL_Point map_click) const override;
    void setInventoryIndex(int inventory_i) const override;
    void execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, const std::string& s_input) const override;
};

class ItemClickedState : public IConsoleCommandState{
public:
    explicit ItemClickedState(EventMediator* eventMediator);
    void setMapClick(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SDL_Point map_click) const override;
    void setInventoryIndex(int inventory_i) const override;
    void execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, const std::string& s_input) const override;
};


#endif //ARGENTUM_CLIENT_CONSOLE_COMMAND_STATE_H
