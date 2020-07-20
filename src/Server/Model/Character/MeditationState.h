//
// Created by franco on 19/7/20.
//

#ifndef ARGENTUM_MEDITATIONSTATE_H
#define ARGENTUM_MEDITATIONSTATE_H

class PlayableCharacter;

class MeditationState {
public:
    virtual void playerMeditatedFor(PlayableCharacter* character, float seconds) = 0;
    virtual ~MeditationState() = default;
};


#endif //ARGENTUM_MEDITATIONSTATE_H
