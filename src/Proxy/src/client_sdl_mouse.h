//
// Created by agustin on 26/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_MOUSE_H
#define ARGENTUM_CLIENT_SDL_MOUSE_H

#include "common_blocking_queue.h"
#include "common_message.h"
#include "client_imediator.h"

class SdlCamera;
class SdlMouse : public BaseComponent {
private:
    SdlCamera& camera;
    SDL_Point position;
    int inventory_clicked_index;
    int right_click;
    bool clicked_in_map;

public:
    explicit SdlMouse(SdlCamera& camera);

    void handleEvent(SDL_Event &event, bool &is_event_handled);

    SDL_Point getPosition();

    bool clickedInMap();

    void setLastClickedItemIndex(int i);

    void clear();

    void use(BlockingQueue<std::unique_ptr<Message>> &clientEvents);

    int getLastClickedItemIndex() const;
};


#endif //ARGENTUM_CLIENT_SDL_MOUSE_H
