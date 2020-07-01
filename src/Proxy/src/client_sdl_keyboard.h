//
// Created by agustin on 30/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_KEYBOARD_H
#define ARGENTUM_CLIENT_SDL_KEYBOARD_H


#include "common_blocking_queue.h"
#include "common_message.h"

class SdlKeyboard {
private:
    int player_vel_x;
    int player_vel_y;
    const int VEL = 1;
public:
    SdlKeyboard();

    void handleEvent(SDL_Event &e, bool &is_event_handled);

    void movePlayer(BlockingQueue<std::unique_ptr<Message>> &clientEvents);
};


#endif //ARGENTUM_CLIENT_SDL_KEYBOARD_H
