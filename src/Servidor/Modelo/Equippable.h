//
// Created by franco on 23/6/20.
//

#ifndef ARGENTUM_EQUIPPABLE_H
#define ARGENTUM_EQUIPPABLE_H

class Equippable {
    int minValue;
    int maxValue;
    public:
        Equippable(int minValue, int maxValue);
        int randomize() const;
};


#endif //ARGENTUM_EQUIPPABLE_H
