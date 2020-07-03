//
// Created by agustin on 3/7/20.
//

#include "client_sdl_music.h"
#include "client_sdl_exception.h"

SdlMusic::SdlMusic(const std::string &path) :
    p_music(nullptr){
        this->loadMusic(path);
}

void SdlMusic::loadMusic(const std::string& path){
    this->free();
    p_music = Mix_LoadMUS(path.c_str());
    if(p_music == nullptr){
        throw SdlException("Failed to load music!", Mix_GetError());
    }
}

void SdlMusic::play(const int loops) {
    if(Mix_PlayingMusic() == 0){
        Mix_PlayMusic(p_music,loops);
    }
}

void SdlMusic::pause(const int loops) const {
    if(Mix_PausedMusic() == 0){
        Mix_PauseMusic();
    }
}

void SdlMusic::resume() const{
    if(Mix_PausedMusic() == 1){
        Mix_ResumeMusic();
    }
}

void SdlMusic::stop() const{
    Mix_HaltMusic();
}

void SdlMusic::free(){
    if(p_music){
        Mix_FreeMusic(p_music);
        p_music = nullptr;
    }
}

SdlMusic::~SdlMusic(){
    this->free();
}