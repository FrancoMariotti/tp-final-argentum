//
// Created by franco on 4/7/20.
//

#include "HealCommand.h"

HealCommand::HealCommand(Map *map) : map(map) {}

void HealCommand::execute(std::string username, std::string command, int x, int y) {
    PlayableCharacter* player = map->getPlayer(username);
    map->searchPriestToHeal(player, Position(x, y));
}
