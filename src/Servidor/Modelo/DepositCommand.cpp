//
// Created by franco on 2/7/20.
//

#include "DepositCommand.h"
#include "Banker.h"
#include "PlayableCharacter.h"

DepositCommand::DepositCommand() {}

void DepositCommand::execute(std::string username,std::string command,int x,int y) {
    std::string element = command;
    PlayableCharacter * player = map->getPlayer(username);
    Banker* banker = map->getBankerAtPosition(x,y);
    if(banker) player->deposit(element,banker);
}
