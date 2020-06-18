//
// Created by franco on 18/6/20.
//

#ifndef ARGENTUM_LONGRANGE_H
#define ARGENTUM_LONGRANGE_H


class LongRange : public Range {
public:
     virtual void attack(Character enemy, Position from) override;
};


#endif //ARGENTUM_LONGRANGE_H
