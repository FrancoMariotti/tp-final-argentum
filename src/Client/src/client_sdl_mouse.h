//
// Created by agustin on 26/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_MOUSE_H
#define ARGENTUM_CLIENT_SDL_MOUSE_H

#include "Common/BlockingQueue.h"
#include "Common/Messages/Message.h"
#include "client_imediator.h"

class SdlCamera;
class SdlMouse : public BaseComponent {
private:
    SdlCamera& camera;
    SDL_Point position;
    int inventory_clicked_index;
    int left_click;
    int right_click;
    bool clicked_in_map;

public:
    explicit SdlMouse(SdlCamera& camera);

    void handleEvent(SDL_Event &event, bool &is_event_handled);

    void clear();

    void use();

};


#endif //ARGENTUM_CLIENT_SDL_MOUSE_H
