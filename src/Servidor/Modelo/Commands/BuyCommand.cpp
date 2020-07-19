#include "BuyCommand.h"
#include "Servidor/Modelo/Character/PlayableCharacter.h"

BuyCommand::BuyCommand(Map *map):map(map) {}

void BuyCommand::execute(std::string username, std::string params, int x, int y) {
    PlayableCharacter* player = map->getPlayer(username);

    Priest* priest = map->getPriestAtPosition(Position(x,y));
    if(priest) player->buyFrom(params,priest);
    else {
        Merchant* merchant = map->getMerchantAtPosition(Position(x,y));
        if(merchant) player->buyFrom(params,merchant);
    }
}
