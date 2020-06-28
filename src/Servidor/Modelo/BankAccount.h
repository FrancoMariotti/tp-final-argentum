//
// Created by franco on 27/6/20.
//

#ifndef ARGENTUM_BANKACCOUNT_H
#define ARGENTUM_BANKACCOUNT_H

#include "Inventory.h"

class BankAccount {
    int gold;
    Inventory objects;
public:
    BankAccount();
    void deposit(int amount);
    void deposit(Equippable* object);
    int extractGold(int amount);
    Equippable* extractObject(int index);
};


#endif //ARGENTUM_BANKACCOUNT_H
