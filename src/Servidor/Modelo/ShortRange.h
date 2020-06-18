//
// Created by franco on 18/6/20.
//

#ifndef ARGENTUM_SHORTRANGE_H
#define ARGENTUM_SHORTRANGE_H


#include "Character.h"
#include "Range.h"

class ShortRange : public Range {
    public:
        ShortRange();
        void attack(Character enemy, Position from) override;
        ~ShortRange();
};


#endif //ARGENTUM_SHORTRANGE_H
