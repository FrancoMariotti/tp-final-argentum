//
// Created by franco on 18/6/20.
//

#ifndef ARGENTUM_SHORTRANGE_H
#define ARGENTUM_SHORTRANGE_H


class ShortRange : public Range {
public:
     virtual void attack(Character enemy, Position from) override;
};


#endif //ARGENTUM_SHORTRANGE_H
