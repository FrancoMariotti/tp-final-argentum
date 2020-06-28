//
// Created by franco on 23/6/20.
//

#ifndef ARGENTUM_EQUIPPABLE_H
#define ARGENTUM_EQUIPPABLE_H

class PlayableCharacter;

class Equippable {
    int minValue;
    int maxValue;
    //Corresponde al identifcador de la imagen asociada al equipable
    int imageId;
protected:
    bool equipped;
public:
    Equippable(int minValue, int maxValue);
    int randomize() const;
    virtual void equipTo(PlayableCharacter *character, int index) = 0;
    virtual void unequipFrom(PlayableCharacter *character) = 0;
};


#endif //ARGENTUM_EQUIPPABLE_H
