//
// Created by agustin on 8/6/20.
//

#include "sdl_window.h"
#include "sdl_exception.h"

SdlWindow::SdlWindow(int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        throw SdlException("SDL could not initialize! SDL_Error:", SDL_GetError());
    }
    //Set texture filtering to linear
    if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" )){
        throw SdlException("Warning: Linear texture filtering not enabled!", SDL_GetError());
    }
    //Create window
    m_window = SDL_CreateWindow("SDL_TUTORIAL", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(m_window == nullptr){
        throw SdlException("Window could not be created! SDL_Error:", SDL_GetError());
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr){
        throw SdlException("Renderer could not be created!", SDL_GetError());
    }

}

SdlWindow::~SdlWindow() {
    //Destroy Window
    if(this->m_renderer){
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if(this->m_window){
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}

void SdlWindow::fill(int r, int g, int b, int alpha){
    //Initialize render color
    SDL_SetRenderDrawColor(m_renderer, r, g, b, alpha);
    SDL_RenderClear(m_renderer);
}

void SdlWindow::fill() {
    this->fill(0x33,0x33,0x33,0xFF);
}

void SdlWindow::initPNG() const{
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if(!((IMG_Init(imgFlags)) & imgFlags)){
        throw SdlException("SDL_image could not initialize! SDL_image Error:", IMG_GetError());
    }
}

SDL_Renderer* SdlWindow::getRenderer() const{
    return m_renderer;
}

void SdlWindow::render() {
    SDL_RenderPresent(m_renderer);
}