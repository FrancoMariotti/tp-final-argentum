#include "Banker.h"

void Banker::registerAccount(const std::string& playerName, int initialDeposit = 0) {
    this->accounts[playerName] = initialDeposit;
}

void Banker::deposit(const std::string& playerName, int deposit) {
    this->accounts.at(playerName) += deposit;
}

