//
// Created by franco on 27/6/20.
//

#include "BankAccount.h"

BankAccount::BankAccount() : gold(0), items(100) {}

void BankAccount::deposit(int amount) {
    gold += amount;
}

void BankAccount::deposit(Equippable* object) {
    items.push_back(object);
}

int BankAccount::extract(int amount) {
    if (amount <= gold) {
        gold -= amount;
    }
    return amount;
}

Equippable* BankAccount::extract(std::string itemName) {
    Equippable* item = nullptr;
    for(unsigned int i = 0; i < items.size(); i++) {
        item = items[i];
        if(item->getName() == itemName) {
            items.erase(items.begin() + i);
            return item;
        }
    }
    return nullptr;
}