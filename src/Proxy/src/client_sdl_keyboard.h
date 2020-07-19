//
// Created by agustin on 30/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_KEYBOARD_H
#define ARGENTUM_CLIENT_SDL_KEYBOARD_H


#include "Common/BlockingQueue.h"
#include "Common/Messages/Message.h"
#include "client_imediator.h"

class SdlKeyboard : public BaseComponent {
private:
    int player_vel_x;
    int player_vel_y;
    const int VEL = 1;
    int game_loops_counter;

public:
    SdlKeyboard();

    void handleEvent(SDL_Event &e, bool &is_event_handled);

    void movePlayer();

};


#endif //ARGENTUM_CLIENT_SDL_KEYBOARD_H
