#include "SellCommand.h"
#include "PlayableCharacter.h"

void SellCommand::execute(std::string username, std::string params, int x, int y) {
    PlayableCharacter* player = map->getPlayer(username);
    Merchant* merchant = map->getMerchantAtPosition(Position(x,y));
    if(merchant) player->sellTo(params,merchant);
}

SellCommand::SellCommand(Map *map):map(map) {}
