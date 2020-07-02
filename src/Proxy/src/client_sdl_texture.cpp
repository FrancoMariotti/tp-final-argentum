//
// Created by agustin on 8/6/20.
//

#include "client_sdl_texture.h"
#include "client_sdl_exception.h"
#include "client_sdl_window.h"

SdlTexture::SdlTexture(const std::string &filename, const SdlWindow& window) :
    m_renderer(window.getRenderer()){
    //Initialize
    this->m_height = 0;
    this->m_width = 0;
    this->m_texture = loadFromFile(filename);
}

SdlTexture::SdlTexture(int width, int height, const std::string &filename, const SdlWindow& window) :
        m_renderer(window.getRenderer()){
    //Initialize
    this->m_texture = loadFromFile(filename);
    this->m_width = width;
    this->m_height = height;
}

SdlTexture::SdlTexture(const std::string &text, TTF_Font *font, SDL_Color colour, const SdlWindow &window) :
        m_renderer(window.getRenderer()) {
    loadFromRenderedText(text, colour, font);
}

SdlTexture::SdlTexture(SdlTexture &&other) noexcept :
    m_renderer(other.m_renderer),
    m_texture(other.m_texture),
    m_width(other.m_width),
    m_height(other.m_height){
        other.m_renderer = nullptr;
        other.m_texture = nullptr;
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
    /*Elimina el fondo negro de las texturas*/
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0x00, 0x00));
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

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
void SdlTexture::loadFromRenderedText(const std::string &text,
                                      SDL_Color textColor, TTF_Font *font) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if(textSurface == nullptr){
        throw SdlException("Unable to render text surface!", TTF_GetError());
    }
    this->m_texture = SDL_CreateTextureFromSurface(this->m_renderer, textSurface);
    if (this->m_texture == nullptr){
        throw SdlException("Unable to create texture from rendered text!", TTF_GetError());
    }
    this->m_width = textSurface->w;
    this->m_height = textSurface->h;

    SDL_FreeSurface(textSurface);
}
#endif

void SdlTexture::setColor(const Uint8 red, const Uint8 green, const Uint8 blue) {
    SDL_SetTextureColorMod(m_texture, red, green, blue);
}

void SdlTexture::setBlending(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(m_texture, blending);
}

void SdlTexture::setAlpha(const uint8_t alpha) {
    SDL_SetTextureAlphaMod(m_texture, alpha);
}

void SdlTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, m_width, m_height};
    //Set clip rendering dimensions
    /*if(clip != nullptr){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }*/
    //Render to screen
    SDL_RenderCopyEx(m_renderer, this->m_texture, clip, &renderQuad, angle, center, flip);
}

int SdlTexture::getWidth() const{
    return m_width;
}

int SdlTexture::getHeight() const{
    return m_height;
}

void SdlTexture::free() {
    //Free textures if it exists
    if(m_texture != nullptr){
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
        m_width = 0;
        m_height = 0;
    }
}


SdlTexture::~SdlTexture() {
    //Deallocate
    free();
}
