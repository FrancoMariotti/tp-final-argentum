//
// Created by agustin on 3/7/20.
//

#ifndef ARGENTUM_CLIENT_SDL_AUDIO_MANAGER_H
#define ARGENTUM_CLIENT_SDL_AUDIO_MANAGER_H


#include <string>
#include <map>
#include <vector>
#include "client_sdl_music.h"
#include "client_sdl_chunk.h"

class SdlAudioManager {
private:
    const std::string AUDIO_PATH = "../../Proxy/audio";

    SdlMusic mainMenuMusic;
    SdlMusic worldMusic;
    std::vector<SdlMusic> game_music;
    std::map<std::string, SdlChunk> game_sounds;


public:
    /*Ctor: carga todos los audios a utilizar durante el juego
     * y la maxima cantidad de sonidos que se pueden escuchar*/
    SdlAudioManager();

    void playMainMenuMusic(const int loops);

    void playSound(const std::string &music_key, int loops);

    void playWorldMusic(const int loops);

    void playRandomAmbientSound(int probability);
};


#endif //ARGENTUM_CLIENT_SDL_AUDIO_MANAGER_H
