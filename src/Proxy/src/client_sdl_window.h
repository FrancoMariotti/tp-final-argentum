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
    int _width, _height;

public:
    SdlWindow(int width, int height);
    ~SdlWindow();
    /*Permite carga de PNG*/
    void initPNG() const;
    /*Permite uso de True type fonts para renderizar texto*/
    void initTTF() const;
    /*Habilita el uso de audio*/
    void initMix();
    /*Pinta la pantalla*/
    void fill(int r, int g, int b, int alpha);
    void fill();
    /*Renderiza en pantalla lo que tiene el SDL_Renderer*/
    void render();
    SDL_Renderer* getRenderer() const;
    int getHeight() const;
    int getWidth() const;
};


#endif //SDLTEST_SDL_WINDOW_H
