//
// Created by franco on 5/7/20.
//

#include "GoldBag.h"
#include "PlayableCharacter.h"

GoldBag::GoldBag(int goldAmount) : goldAmount(goldAmount) {}

void GoldBag::takenBy(PlayableCharacter *player) {
    player->takeDroppable(this);
}

int GoldBag::getAmount() const {
    return goldAmount;
}
