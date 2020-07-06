//
// Created by agustin on 3/7/20.
//

#include "client_sdl_audio_manager.h"
#include "../../Servidor/Common/Utils.h"


SdlAudioManager::SdlAudioManager() :
        mainMenuMusic(AUDIO_PATH + "/world.mp3"),
        worldMusic(AUDIO_PATH + "/main_menu.mp3"){

    game_music.emplace_back(AUDIO_PATH + "/main_menu.mp3");
    game_music.emplace_back(AUDIO_PATH + "/world.mp3");
    game_sounds.emplace(std::make_pair("death", SdlChunk(AUDIO_PATH + "/death.wav")));
    game_sounds.emplace(std::make_pair("explosion", SdlChunk(AUDIO_PATH + "/explosion.wav")));
    game_sounds.emplace(std::make_pair("heal", SdlChunk(AUDIO_PATH + "/heal.wav")));
    game_sounds.emplace(std::make_pair("magic_arrow", SdlChunk(AUDIO_PATH + "/magic_arrow.wav")));
    game_sounds.emplace(std::make_pair("missile", SdlChunk(AUDIO_PATH + "/missile.wav")));
    game_sounds.emplace(std::make_pair("step1", SdlChunk(AUDIO_PATH + "/step1.wav")));
    game_sounds.emplace(std::make_pair("step2", SdlChunk(AUDIO_PATH + "/step2.wav")));
    game_sounds.emplace(std::make_pair("equip", SdlChunk(AUDIO_PATH + "/equip.wav")));
    game_sounds.emplace(std::make_pair("arrow", SdlChunk(AUDIO_PATH + "/arrow.wav")));
    game_sounds.emplace(std::make_pair("dodge", SdlChunk(AUDIO_PATH + "/dodge.wav")));
    game_sounds.emplace(std::make_pair("ambient1", SdlChunk(AUDIO_PATH + "/ambient1.wav")));
    game_sounds.emplace(std::make_pair("ambient2", SdlChunk(AUDIO_PATH + "/ambient2.wav")));
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

void SdlAudioManager::playRandomAmbientSound(int rarity){
    int rand = Utils::random_int_number(0, rarity);
    if (!Mix_Playing(0)){
        if (rand < 4){
            game_sounds.at("ambient1").play(0, 0);
        }
        if (rand < 2) {
            game_sounds.at("ambient2").play(0, 0);
        }
    }
}

void SdlAudioManager::reproduceRelatedSound(const std::string& message){
    if(message == "Ataque esquivado"){
        game_sounds.at("dodge").play(0);
    } else if (message.find("Danio recibido") != std::string::npos){
        game_sounds.at("step2").play(0);
    }
}