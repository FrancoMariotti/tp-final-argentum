//
// Created by franco on 5/7/20.
//

#include "GoldBag.h"
#include "Server/Model/Character/PlayableCharacter.h"

GoldBag::GoldBag(int goldAmount) : goldAmount(goldAmount) {}

void GoldBag::takenBy(PlayableCharacter *player, Position& position) {
    player->takeDroppable(this, position);
}

int GoldBag::getAmount() const {
    return goldAmount;
}
