//
// Created by franco on 5/7/20.
//

#ifndef ARGENTUM_ITEMSELLER_H
#define ARGENTUM_ITEMSELLER_H
#include "string"
#include "Equippable.h"

class ItemSeller{
public:
    virtual Equippable* sell(const std::string& name, int *gold) = 0;
};

#endif //ARGENTUM_ITEMSELLER_H
