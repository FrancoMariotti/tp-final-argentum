#include "BuyCommand.h"


BuyCommand::BuyCommand(Map *map):map(map) {}

void BuyCommand::execute(std::string username, std::string params, int x, int y) {
    PlayableCharacter* player = map->getPlayer(username);
    map->buyFromMerchant(player,Position(x,y),params);
}
