//
// Created by agustin on 30/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_KEYBOARD_H
#define ARGENTUM_CLIENT_SDL_KEYBOARD_H


#include "Common/BlockingQueue.h"
#include "Common/Message.h"
#include "client_imediator.h"

class SdlKeyboard : public BaseComponent {
private:
    int player_vel_x;
    int player_vel_y;
    const int VEL = 1;
    bool handle_events;
    int game_loops_counter;

public:
    SdlKeyboard();

    void handleEvent(SDL_Event &e, bool &is_event_handled);

    void movePlayer(BlockingQueue<std::unique_ptr<Message>> &clientEvents);

    void setEventHandling(bool handle, const int game_loops);
};


#endif //ARGENTUM_CLIENT_SDL_KEYBOARD_H
