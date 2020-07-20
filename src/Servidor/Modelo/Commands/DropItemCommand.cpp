//
// Created by franco on 5/7/20.
//

#include "DropItemCommand.h"
#include "Servidor/Modelo/Character/PlayableCharacter.h"

DropItemCommand::DropItemCommand(Map *map) : map(map){}

void DropItemCommand::execute(std::string username, std::string params, int x, int y) {
    PlayableCharacter* player = map->getPlayer(username);
    int itemIndex = x;
    player->dropItem(itemIndex);
}
