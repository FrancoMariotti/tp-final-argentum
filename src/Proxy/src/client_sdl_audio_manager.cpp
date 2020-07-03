//
// Created by agustin on 3/7/20.
//

#include "client_sdl_audio_manager.h"


SdlAudioManager::SdlAudioManager() :
        mainMenuMusic(AUDIO_PATH + "/world.mp3"),
        worldMusic(AUDIO_PATH + "/main_menu.mp3"){

    game_sounds.emplace(std::make_pair("death", SdlChunk(AUDIO_PATH + "/death.wav")));
    game_sounds.emplace(std::make_pair("explosion", SdlChunk(AUDIO_PATH + "/explosion.wav")));
    game_sounds.emplace(std::make_pair("heal", SdlChunk(AUDIO_PATH + "/heal.wav")));
    game_sounds.emplace(std::make_pair("magic_arrow", SdlChunk(AUDIO_PATH + "/magic_arrow.wav")));
    game_sounds.emplace(std::make_pair("missile", SdlChunk(AUDIO_PATH + "/missile.wav")));
    game_sounds.emplace(std::make_pair("step1", SdlChunk(AUDIO_PATH + "/step1.wav")));
    game_sounds.emplace(std::make_pair("step2", SdlChunk(AUDIO_PATH + "/step2.wav")));
}

void SdlAudioManager::playMainMenuMusic(const int loops) {
    mainMenuMusic.play(loops);
}

void SdlAudioManager::playWorldMusic(const int loops) {
    mainMenuMusic.stop();
    worldMusic.play(loops);
}

void SdlAudioManager::playSound(const std::string& music_key, const int loops){
    game_sounds.at(music_key).play(loops);
}