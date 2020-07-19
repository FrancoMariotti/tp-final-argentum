#include "Priest.h"
#include <utility>
#include "Servidor/Modelo/Character/PlayableCharacter.h"

Priest::Priest(std::vector<Position> positions, std::map<std::string, item_t> stock ,
        ItemFactory* itemFactory):
        ItemSeller(std::move(stock), itemFactory), positions(std::move(positions)) {}
/*
Equippable* Priest::sell(const std::string& name, int *gold) {
    if (stock.find(name) == stock.end()) return nullptr;
    item_t item = stock.at(name);
    if (item.goldCost > *gold) return nullptr;
    *gold -= item.goldCost;
    if (*gold < 0) *gold = 0;
    return itemFactory->create(item);
}
*/
void Priest::restoreManaAndLife(PlayableCharacter* character) {
    character->healedByPriest();
}

void Priest::revive(PlayableCharacter* character) {
    character->revive();
}

void Priest::reviveIn(PlayableCharacter *character, const Position& position) {
    character->teleportTo(position);
    character->revive();
}
/*
Priest& Priest::operator=(Priest&& priest) noexcept {
    this->factories = std::move(priest.factories);
    this->positions = std::move(priest.positions);
    this->stock = std::move(priest.stock);
    return *this;
}

Priest::Priest(Priest &&priest) noexcept: positions(priest.positions),
                            stock(priest.stock),factories(priest.factories) {
    priest.factories.clear();
}
*/
bool Priest::ocupies(const Position& position) {
    for (Position & pos : positions) {
        if (pos == position) return true;
    }
    return false;
}

Position Priest::closestPositionTo(PlayableCharacter *player) {
    int minDistance = -1;
    int currDistance;
    Position nearestPosition(0,0);
    for (Position & position : positions) {
        currDistance = player->distanceTo(position);
        if (minDistance < 0 || currDistance < minDistance) {
            minDistance = currDistance;
            nearestPosition = position;
        }
    }
    return nearestPosition;
}

Priest::~Priest(){
   /* auto it = factories.begin();
    for(;it!=factories.end();it++) {
        delete it->second;
    }*/
}

void Priest::sendStockListTo(PlayableCharacter *pCharacter) {
    std::string message = "Items del sacerdote en venta: ";
    for (auto &item : stock) {
        message += item.first + " ";
    }
    std::vector<std::string> messages;
    messages.push_back(message);
    pCharacter->notifyConsoleOutputUpdate(messages);
}

