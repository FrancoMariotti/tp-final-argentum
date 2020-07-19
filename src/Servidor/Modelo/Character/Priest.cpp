#include "Priest.h"
#include <utility>
#include "Servidor/Modelo/Character/PlayableCharacter.h"

Priest::Priest(std::vector<Position> positions, std::map<std::string, item_t> stock ,
        ItemFactory* itemFactory):
        ItemSeller(std::move(stock), itemFactory), positions(std::move(positions)) {}
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

void Priest::sendStockListTo(PlayableCharacter *pCharacter) {
    std::string message = "Items del sacerdote en venta: ";
    for (auto &item : stock) {
        message += item.first + " ";
    }
    std::vector<std::string> messages;
    messages.push_back(message);
    pCharacter->notifyConsoleOutputUpdate(messages);
}

Priest::~Priest(){
   /* auto it = factories.begin();
    for(;it!=factories.end();it++) {
        delete it->second;
    }*/
}

