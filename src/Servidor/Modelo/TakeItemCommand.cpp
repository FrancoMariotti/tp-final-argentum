//
// Created by franco on 5/7/20.
//

#include "TakeItemCommand.h"
#include "PlayableCharacter.h"

TakeItemCommand::TakeItemCommand(Map *map) : map(map) {}

void TakeItemCommand::execute(std::string username, std::string params, int x, int y) {
    PlayableCharacter* player = map->getPlayer(username);
    player->takeDrop();
}
