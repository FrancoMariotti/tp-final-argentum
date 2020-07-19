//
// Created by franco on 19/7/20.
//

#ifndef ARGENTUM_NOTMEDITATING_H
#define ARGENTUM_NOTMEDITATING_H


#include "MeditationState.h"

class PlayableCharacter;

class NotMeditating : public MeditationState {
    void playerMeditatedFor(PlayableCharacter* character, float seconds) override;
};


#endif //ARGENTUM_NOTMEDITATING_H
