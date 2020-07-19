//
// Created by franco on 6/7/20.
//

#include "ListItemsCommand.h"
#include "Servidor/Modelo/Character/PlayableCharacter.h"

ListItemsCommand::ListItemsCommand(Map *map) : map(map) {}

void ListItemsCommand::execute(std::string username, std::string command, int x, int y) {
    PlayableCharacter* player = map->getPlayer(username);
    Banker* banker = map->getBankerAtPosition(Position(x,y));
    Merchant* merchant = map->getMerchantAtPosition(Position(x, y));
    Priest* priest = map->getPriestAtPosition(Position(x, y));
    if (banker) player->sendItemsInBankList();
    else if (merchant) merchant->sendStockListTo(player);
    else if (priest) priest->sendStockListTo(player);
}
