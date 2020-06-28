//
// Created by agustin on 26/6/20.
//

#ifndef ARGENTUM_CLIENT_SDL_MOUSE_H
#define ARGENTUM_CLIENT_SDL_MOUSE_H

class SdlCamera;
class SdlMouse {
private:
    SdlCamera& camera;
    SDL_Point position;

    bool clicked_in_map;

public:
    explicit SdlMouse(SdlCamera& camera);

    void handleEvent(SDL_Event &event, bool &is_event_handled);

    SDL_Point getPosition();

    bool clickedInMap();
};


#endif //ARGENTUM_CLIENT_SDL_MOUSE_H
