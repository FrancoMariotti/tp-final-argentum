//
// Created by franco on 27/6/20.
//

#include <algorithm>
#include "BankAccount.h"
#include "PlayableCharacter.h"

BankAccount::BankAccount() : gold(0) {}

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

Equippable* BankAccount::extract(const std::string& itemName) {
    Equippable* item = nullptr;
    auto itr = items.begin();
    for (;itr != items.end(); ++itr) {
        if(!(*itr)) continue;
        if ((*itr)->getName() ==  itemName) {
            item = *itr;
            items.erase(itr--);
            break;
        }
    }

    /*items.erase(std::remove_if(items.begin(),
                               items.end(),
                                  [itemName](Equippable * equippable){
                                        if (equippable) return equippable->getName() == itemName;
                                        return false;
                                    }),
                   items.end());*/

    return item;
}

void BankAccount::sendItemsList(PlayableCharacter *owner) {
    std::string message = "Items depositados en el banco: ";
    for (auto &item : items) {
        message += item->getName() + " ";
    }
    std::vector<std::string> messages;
    messages.push_back(message);
    owner->notifyConsoleOutputUpdate(messages);
}
