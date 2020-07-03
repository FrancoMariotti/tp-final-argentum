#include "Banker.h"
/*
void Banker::registerAccount(const std::string& playerName) {
    this->accounts[playerName] = BankAccount();
}
*/

Banker::Banker(Position pos) : pos(pos) {}

void Banker::deposit(BankAccount* account, int deposit) {
    account->deposit(deposit);
}

void Banker::deposit(BankAccount* account, Equippable* object) {
     account->deposit(object);
}

int Banker::extract(BankAccount* account, int amount) {
   return account->extract(amount);
}

Equippable* Banker::extract(BankAccount* account, std::string itemName) {
    return account->extract(itemName);
}

