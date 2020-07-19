//
// Created by franco on 19/7/20.
//

#include "Meditating.h"
#include "PlayableCharacter.h"

void Meditating::playerMeditatedFor(PlayableCharacter *character, float seconds) {
    character->meditatedFor(seconds);
}
