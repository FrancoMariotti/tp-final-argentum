//
// Created by franco on 19/7/20.
//

#ifndef ARGENTUM_MEDITATING_H
#define ARGENTUM_MEDITATING_H


#include "MeditationState.h"

class Meditating : public MeditationState {
    void playerMeditatedFor(PlayableCharacter* character, float seconds) override;
};


#endif //ARGENTUM_MEDITATING_H
