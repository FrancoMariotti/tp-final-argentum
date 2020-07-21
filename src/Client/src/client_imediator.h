//
// Created by agustin on 6/7/20.
//

#ifndef ARGENTUM_CLIENT_IMEDIATOR_H
#define ARGENTUM_CLIENT_IMEDIATOR_H


#include <SDL2/SDL_rect.h>
#include <string>

class SdlConsole;
class SdlButton;
class BaseComponent;
class IMediator {
public:
    virtual void notify(BaseComponent* component, SDL_Point  right_click) = 0;
    virtual void notify(BaseComponent* component) = 0;
    virtual void notify(SdlConsole *console, const std::string& s_input) = 0;
    virtual void notify(BaseComponent *sender, SDL_Point left_click, int overload) = 0;
    virtual void notify(BaseComponent *sender, int i) = 0;
    virtual void notify(BaseComponent *sender, int vel_x, int vel_y) = 0;
};

class BaseComponent {
protected:
    IMediator* mediator;
public:
    explicit BaseComponent(IMediator* mediator = nullptr) : mediator(mediator){};

    void setMediator(IMediator* new_mediator){
        this->mediator = new_mediator;
    }

};



#endif //ARGENTUM_CLIENT_IMEDIATOR_H
