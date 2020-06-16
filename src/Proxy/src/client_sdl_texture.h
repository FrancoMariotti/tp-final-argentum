//
// Created by agustin on 8/6/20.
//

#ifndef SDLTEST_SDL_TEXTURE_H
#define SDLTEST_SDL_TEXTURE_H


#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class SdlWindow;
class SdlTexture {
private:
    //The actual hardware texture
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;

    //Image dimensions
    int m_width;
    int m_height;

public:
    /*Ctor usa el tamaño de la imagen*/
    SdlTexture(const std::string &filename, const SdlWindow& window);

    /*Ctor con imagen de ancho @param width y alto @param height */
    SdlTexture(int width, int height, const std::string &filename, const SdlWindow &window);

    //Constructor para crear texturas a partir de texto
    SdlTexture(const std::string &text, TTF_Font *font, SDL_Color colour, const SdlWindow &window);

    SdlTexture(const SdlTexture& other) = delete;

    SdlTexture(SdlTexture&& other) noexcept;

    //Deallocates memory
    ~SdlTexture();

    //Loads image at specified path
    SDL_Texture * loadFromFile(const std::string &path);

    //Clase SDL-QT
    SDL_Texture *loadTexture(const std::string &filename);

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
    //Creates image from font string
    void loadFromRenderedText(const std::string &text, SDL_Color textColor, TTF_Font *font);
#endif

    //Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    //Set blending
    void setBlending(SDL_BlendMode blending);

    //Set alpha modulation
    void setAlpha(uint8_t alpha);

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = nullptr,
                 double angle = 0.0, SDL_Point* center = nullptr,
                 SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Gets image dimensions
    int getWidth() const;
    int getHeight() const;

    //Deallocates texture
    void free();

};


#endif //SDLTEST_SDL_TEXTURE_H
