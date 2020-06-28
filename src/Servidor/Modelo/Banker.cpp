#include "Banker.h"

void Banker::registerAccount(const std::string& playerName) {
    this->accounts[playerName] = BankAccount();
}

void Banker::deposit(const std::string& playerName, int deposit) {
    this->accounts.at(playerName).deposit(deposit);
}

void Banker::deposit(const std::string& playerName, Equippable* object) {
     this->accounts.at(playerName).deposit(object);
}

int Banker::extractGold(const std::string& playerName, int amount) {
   return this->accounts.at(playerName).extractGold(amount);
}

Equippable* Banker::extractObject(const std::string& playerName, int index) {
    return this->accounts.at(playerName).extractObject(index);
}

