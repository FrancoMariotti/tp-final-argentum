//
// Created by agustin on 2/7/20.
//

#include "client_sdl_chunk.h"
#include "client_sdl_exception.h"

SdlChunk::SdlChunk(const std::string& path) :
    p_chunk(nullptr){
        this->loadWAV(path);
}

SdlChunk::SdlChunk(SdlChunk &&other) noexcept :
        p_chunk(other.p_chunk){
    other.p_chunk = nullptr;
}

void SdlChunk::loadWAV(const std::string& path){
    this->free();
    p_chunk = Mix_LoadWAV(path.c_str());
    if(p_chunk == nullptr){
        throw SdlException("Failed to load WAV", Mix_GetError());
    }
}

void SdlChunk::play(const int loops, const int channel) {
    Mix_PlayChannel(channel, p_chunk, loops);
}

void SdlChunk::free(){
    if(p_chunk){
        Mix_FreeChunk(p_chunk);
        p_chunk = nullptr;
    }
}

SdlChunk::~SdlChunk(){
    this->free();
}
