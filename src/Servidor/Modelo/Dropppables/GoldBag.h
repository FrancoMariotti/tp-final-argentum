//
// Created by franco on 5/7/20.
//

#ifndef ARGENTUM_GOLDBAG_H
#define ARGENTUM_GOLDBAG_H


#include "Servidor/Modelo/Dropppables/Droppable.h"

class PlayableCharacter;

class GoldBag : public Droppable {
    int goldAmount;
public:
    GoldBag(int goldAmount);
    void takenBy(PlayableCharacter* player) override;

    int getAmount() const;
};


#endif //ARGENTUM_GOLDBAG_H
