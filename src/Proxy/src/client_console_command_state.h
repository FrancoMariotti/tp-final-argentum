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
    virtual void setMapClick(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SDL_Point map_click) = 0;
    virtual void setInventoryIndex(const int inventory_i) = 0;
    virtual void execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, const std::string& s_input) = 0;
    virtual ~IConsoleCommandState() = default;
};

class WaitingState : public IConsoleCommandState{
public:
    explicit WaitingState(EventMediator* eventMediator);
    void setMapClick(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SDL_Point map_click) override;
    void setInventoryIndex(int inventory_i) override;
    void execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, const std::string& s_input) override;
};


class MapClickedState : public IConsoleCommandState{
public:
    explicit MapClickedState(EventMediator* eventMediator);
    void setMapClick(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SDL_Point map_click) override;
    void setInventoryIndex(int inventory_i) override;
    void execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, const std::string& s_input) override;
};

class ItemClickedState : public IConsoleCommandState{
public:
    explicit ItemClickedState(EventMediator* eventMediator);
    void setMapClick(BlockingQueue<std::unique_ptr<Message>> &clientEvents, SDL_Point map_click) override;
    void setInventoryIndex(int inventory_i) override;
    void execute(BlockingQueue<std::unique_ptr<Message>> &clientEvents, const std::string& s_input) override;
};


#endif //ARGENTUM_CLIENT_CONSOLE_COMMAND_STATE_H
