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
    /*Creo un unico sonido a ser utilizado*/
    explicit SdlChunk(const std::string& path);
    SdlChunk(const SdlChunk& other) = delete;
    SdlChunk(SdlChunk&& other);
    /*Cargo el sonido correspondiente a @param path
     * se puede usar para asignar un nuevo sonido*/
    void loadWAV(const std::string &path);
    /*Reproduce el sonido 1 + @param loops veces, en un channel
     * que no este reservado*/
    void play(const int loops);
    ~SdlChunk();

private:
    void free();
};


#endif //ARGENTUM_CLIENT_SDL_CHUNK_H
