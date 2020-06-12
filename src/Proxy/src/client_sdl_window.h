//
// Created by agustin on 8/6/20.
//

#ifndef SDLTEST_SDL_WINDOW_H
#define SDLTEST_SDL_WINDOW_H

#include <SDL2/SDL_image.h>

class SdlWindow {
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

public:
    SdlWindow(int width, int height);
    ~SdlWindow();
    void initPNG() const;
    void fill(int r, int g, int b, int alpha);
    void fill();
    void render();
    SDL_Renderer* getRenderer() const;
};


#endif //SDLTEST_SDL_WINDOW_H
