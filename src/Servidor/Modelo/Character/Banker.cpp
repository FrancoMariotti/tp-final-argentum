#include "Banker.h"

#include <utility>

Banker::Banker(std::vector<Position> positions) : positions(std::move(positions)) {}


void Banker::deposit(BankAccount *account, int deposit, int &gold) {
    if(gold >= deposit) {
        account->deposit(deposit);
        gold -= deposit;
    }
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

bool Banker::ocupies(const Position &position) {
    for (Position & pos : positions) {
        if (pos == position) return true;
    }
    return false;
}

