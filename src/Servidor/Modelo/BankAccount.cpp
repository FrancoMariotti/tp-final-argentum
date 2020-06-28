//
// Created by franco on 27/6/20.
//

#include "BankAccount.h"

BankAccount::BankAccount() : gold(0), objects(100) {}

void BankAccount::deposit(int amount) {
    gold += amount;
}

void BankAccount::deposit(Equippable* object) {
    objects.store(object);
}

int BankAccount::extractGold(int amount) {
    if (amount <= gold) {
        gold -= amount;
    }
    return amount;
}

Equippable* BankAccount::extractObject(int index) {
    return objects.takeElement(index);
}