//
// Created by franco on 4/7/20.
//

#include "ReviveCommand.h"
#include "PlayableCharacter.h"

ReviveCommand::ReviveCommand(Map *map): map(map){}

void ReviveCommand::execute(std::string username,std::string params,int x,int y) {
     PlayableCharacter* player = map->getPlayer(username);
     Priest* priest = map->getPriestAtPosition(Position(x,y));
     if (x >= 0 && y >= 0 && priest && player->isInCity()) {
         priest->revive(player);
     } else  if (x == -1 && y == -1) {
         Position position = map->getRandomPosAtClosestPriestCity(player);
         map->reviveIn(player, position);
     }
}
