//
// Created by franco on 4/7/20.
//

#include "ReviveCommand.h"
#include "PlayableCharacter.h"

ReviveCommand::ReviveCommand(Map *map): map(map){}

void ReviveCommand::execute(std::string username,std::string command,int x,int y) {
     PlayableCharacter* player = map->getPlayer(username);
     if (x >= 0 && y >= 0) {
         map->searchPriestToRevive(player, Position(x, y));
     } else {
         map->reviveNextToClosestPriest(player);
     }
}
