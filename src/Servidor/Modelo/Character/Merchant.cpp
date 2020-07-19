#include <utility>
#include "Merchant.h"
#include "Servidor/Modelo/Factory.h"
#include "Servidor/Modelo/Character/PlayableCharacter.h"

Merchant::Merchant(std::vector<Position> positions, std::map<std::string, item_t> stock ,
                   ItemFactory* itemFactory):
                   ItemSeller(std::move(stock), itemFactory), positions(std::move(positions)){}

int Merchant::buy(const std::string& itemName) {
    if (stock.find(itemName) == stock.end()) return 0;
    return stock.at(itemName).goldCost;
}

bool Merchant::ocupies(Position position) {
    for (Position & pos : positions) {
        if (pos == position) return true;
    }
    return false;
}

Merchant::~Merchant() {}

void Merchant::sendStockListTo(PlayableCharacter *pCharacter) {
    std::string message = "Items del comerciante en venta: ";
    for (auto &item : stock) {
        message += item.first + " ";
    }
    std::vector<std::string> messages;
    messages.push_back(message);
    pCharacter->notifyConsoleOutputUpdate(messages);
}