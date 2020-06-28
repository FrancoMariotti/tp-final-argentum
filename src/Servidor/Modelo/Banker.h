#ifndef ARGENTUM_BANKER_H
#define ARGENTUM_BANKER_H
#include "map"
#include "BankAccount.h"

class Banker {
    std::map<std::string, BankAccount> accounts;
public:
    void registerAccount(const std::string &playerName);
    void deposit(const std::string &playerName, int deposit);
    void deposit(const std::string& playerName, Equippable* object);
    int extractGold(const std::string& playerName, int amount);
    Equippable* extractObject(const std::string& playerName, int index);
};


#endif //ARGENTUM_BANKER_H
