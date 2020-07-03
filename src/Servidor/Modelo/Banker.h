#ifndef ARGENTUM_BANKER_H
#define ARGENTUM_BANKER_H
#include "map"
#include "BankAccount.h"
#include "Position.h"


class Banker {
    friend class City;
    Position pos;
public:
    explicit Banker(Position pos);
    //void registerAccount(const std::string &playerName);
    void deposit(BankAccount* account, int deposit);
    void deposit(BankAccount* account, Equippable* object);
    int extract(BankAccount* account, int amount);
    Equippable* extract(BankAccount* account, std::string itemName);
};


#endif //ARGENTUM_BANKER_H
