//
// Created by agustin on 2/7/20.
//

#include "client_sdl_chunk.h"
#include "client_sdl_exception.h"

/*Creo un unico sonido a ser utilizado*/
SdlChunk::SdlChunk(const std::string& path) {
    p_chunk = Mix_LoadWAV(path.c_str());
    if(p_chunk == nullptr){
        throw SdlException("Failed to load beat music!", Mix_GetError());
    }
}

/*Reproduce el sonido 1 + @param loops veces, en un channel que no este reservado*/
void SdlChunk::play(const int loops) {
    Mix_PlayChannel(-1, p_chunk, loops);
}

SdlChunk::~SdlChunk(){
    Mix_FreeChunk(p_chunk);
    p_chunk = nullptr;
}