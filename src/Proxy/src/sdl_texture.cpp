//
// Created by agustin on 8/6/20.
//

#include "sdl_texture.h"
#include "sdl_exception.h"
#include "sdl_window.h"

SdlTexture::SdlTexture(const std::string &filename, const SdlWindow& window) :
    m_renderer(window.getRenderer()){
    //Initialize
    this->m_height = 0;
    this->m_width = 0;
    this->m_texture = loadFromFile(filename);
}

SdlTexture::SdlTexture(int screen_width, int screen_height, const std::string &filename, const SdlWindow& window) :
        m_renderer(window.getRenderer()){
    //Initialize
    this->m_texture = loadFromFile(filename);
    this->m_width = screen_width;
    this->m_height = screen_height;
}

//Este constructor lo agregue para crear textura a partir de un string
SdlTexture::SdlTexture(std::string text, std::string fontPath, SDL_Color colour,
        int width, int height, const SdlWindow& window) :
        m_renderer(window.getRenderer()), m_width(width), m_height(height) {
    this->m_texture = loadFromText(text, fontPath, colour);
}

SdlTexture::~SdlTexture() {
    //Deallocate
    free();
}

SDL_Texture *SdlTexture::loadTexture(const std::string &filename) {
    SDL_Texture* texture = IMG_LoadTexture(this->m_renderer,
                                           filename.c_str());
    if (!texture) {
        throw SdlException("Error al cargar la textura", SDL_GetError());
    }

    return texture;
}

SDL_Texture* SdlTexture::loadFromFile(const std::string &path) {
    //Get rid of preexisting texture
    /**Puede producir SIGSEV*/
    //free();

    //The final texture
    SDL_Texture* newTexture = nullptr;
    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == nullptr){
        throw SdlException("Unable to load image SDL_image Error:", SDL_GetError());
    }
    //Color key image
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
    if(newTexture == nullptr){
        throw SdlException("Unable to create texture", SDL_GetError());
    }
    //Get Image dimensions
    this->m_width = loadedSurface->w;
    this->m_height = loadedSurface->h;

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

    return newTexture;
}

SDL_Texture* SdlTexture::loadFromText(std::string text, std::string fontPath, SDL_Color colour) {
    //Abro la fuente
    TTF_Font* fontType = TTF_OpenFont(fontPath.c_str(), 255);
    if (!fontType) {
        throw SdlException("Could not open font in loadFromText function", TTF_GetError());
    }
    //Creo superficie a partir del texto ingresado
    SDL_Surface* textSurface = TTF_RenderText_Solid(fontType, text.c_str(), colour);
    if(!textSurface) {
        throw SdlException("Error in TTF render text in loadFromText function", TTF_GetError());
    }
    //Creo textura a partir de una superficie
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    if(!textTexture) {
         throw SdlException("Error in creating texture from surface", SDL_GetError());
    }

    SDL_FreeSurface(textSurface);

    return textTexture;
}

/*
#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
int SdlTexture::loadFromRenderedText(const std::string &textureText, SDL_Color textColor) {
    free();
    //Usamos TTF en vez de SDL para el textSurface (ex loadedSurface)
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont,textureText.c_str(), textColor);
    if(textSurface == nullptr){
        throw SdlException("Unable to render text surface!", TTF_GetError());
    }
    this->m_texture = SDL_CreateTextureFromSurface(this->m_renderer, textSurface);
    if (this->m_texture == nullptr){
        throw SdlException("Unable to create texture from rendered text!", TTF_GetError());
    }
    //Get Image dimensiones
    this->m_width = textSurface->w;
    this->m_height = textSurface->h;

    //Get rid of old loaded surface
    SDL_FreeSurface(textSurface);

    return 0;
}
#endif
*/

void SdlTexture::free() {
    //Free textures if it exists
    if(m_texture != nullptr){
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
        m_width = 0;
        m_height = 0;
    }
}

void SdlTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(m_texture, red, green, blue);
}

void SdlTexture::setBlending(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(m_texture, blending);
}

void SdlTexture::setAlpha(uint8_t alpha) {
    SDL_SetTextureAlphaMod(m_texture, alpha);
}

void SdlTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, m_width, m_height};
    //Set clip rendering dimensions
    if(clip != nullptr){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    //Render to screen
    SDL_RenderCopyEx(m_renderer, this->m_texture, clip, &renderQuad, angle, center, flip);
}

int SdlTexture::getWidth() {
    return m_width;
}

int SdlTexture::getHeight() {
    return m_height;
}
