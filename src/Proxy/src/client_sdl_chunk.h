//
// Created by agustin on 2/7/20.
//

#ifndef ARGENTUM_CLIENT_SDL_CHUNK_H
#define ARGENTUM_CLIENT_SDL_CHUNK_H


#include <SDL2/SDL_mixer.h>
#include <string>

class SdlChunk {
private:
    Mix_Chunk* p_chunk;

public:
    explicit SdlChunk(const std::string& path);
    SdlChunk(const SdlChunk& other) = delete;
    void play(const int loops);
    ~SdlChunk();
};


#endif //ARGENTUM_CLIENT_SDL_CHUNK_H
