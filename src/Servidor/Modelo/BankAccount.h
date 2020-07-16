//
// Created by franco on 27/6/20.
//

#ifndef ARGENTUM_BANKACCOUNT_H
#define ARGENTUM_BANKACCOUNT_H

#include "Inventory.h"

class BankAccount {
    friend class Banker;
    int gold;
    std::vector<Equippable*> items;
    void deposit(int amount);
    void deposit(Equippable* object);
    int extract(int amount);
    Equippable* extract(const std::string& itemName);
public:
    BankAccount();
    void sendItemsList(PlayableCharacter *owner);
};


#endif //ARGENTUM_BANKACCOUNT_H
