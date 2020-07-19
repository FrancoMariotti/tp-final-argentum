#ifndef ARGENTUM_BANKER_H
#define ARGENTUM_BANKER_H
#include "map"
#include "Servidor/Modelo/Character/BankAccount.h"
#include "Servidor/Modelo/Map/Position.h"


class Banker {
    std::vector<Position> positions;
public:
    Banker() = default;
    explicit Banker(std::vector<Position> positions);
    void deposit(BankAccount* account, int deposit,int& gold);
    void deposit(BankAccount* account, Equippable* object);
    int extract(BankAccount* account, int amount);
    Equippable* extract(BankAccount* account, std::string itemName);
    bool ocupies(const Position &position);
};


#endif //ARGENTUM_BANKER_H
