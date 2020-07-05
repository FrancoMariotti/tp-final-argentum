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
    /**TODO: guardar atributos widht, height y reemplazar los parametros screen_width, screen height
  * por window en el resto de las clases*/
public:
    SdlWindow(int width, int height);
    ~SdlWindow();
    void initPNG() const;
    void initTTF() const;
    void fill(int r, int g, int b, int alpha);
    void fill();
    void render();
    SDL_Renderer* getRenderer() const;

    void initMix();
};


#endif //SDLTEST_SDL_WINDOW_H
