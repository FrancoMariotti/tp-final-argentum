//
// Created by franco on 4/7/20.
//

#include "ReviveCommand.h"

ReviveCommand::ReviveCommand(Map *map): map(map){}

void ReviveCommand::execute(std::string username,std::string command,int x,int y) {
     PlayableCharacter* player = map->getPlayer(username);
     map->searchPriestToRevive(player, Position(x, y));
}
