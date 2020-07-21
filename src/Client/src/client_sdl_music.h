//
// Created by agustin on 3/7/20.
//

#ifndef ARGENTUM_CLIENT_SDL_MUSIC_H
#define ARGENTUM_CLIENT_SDL_MUSIC_H


#include <SDL2/SDL_mixer.h>
#include <string>

class SdlMusic {
private:
    Mix_Music* p_music;

public:
    /*Ctor*/
    explicit SdlMusic(const std::string& path);
    SdlMusic(const SdlMusic& other) = delete;
    SdlMusic(SdlMusic&& other) noexcept;
    /*Carga la musica ubicada en @param path
     * puede reutilizarse la funcion para cargar una nueva musica*/
    void loadMusic(const std::string& path);
    /*Si no hay musica reproduciendo, reproduce la musica 1 + @param loops veces*/
    void play(int loops);
    /*Si no esta pausada, pausa*/
    void pause(int loops) const;
    /*Si esta pausada, reanuda*/
    void resume() const;
    /*Detiene por completo la reproduccion*/
    void stop() const;
    ~SdlMusic();

private:
    /*Libera los recursos, se llama cada vez que se asigna una nueva musica*/
    void free();
};


#endif //ARGENTUM_CLIENT_SDL_MUSIC_H
