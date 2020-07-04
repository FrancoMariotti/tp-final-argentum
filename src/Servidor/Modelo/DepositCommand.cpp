//
// Created by franco on 2/7/20.
//

#include <iostream>
#include "DepositCommand.h"
#include "PlayableCharacter.h"

DepositCommand::DepositCommand(Map *map): map(map){}

void DepositCommand::execute(std::string username,std::string command,int x,int y) {
    std::string element = command;
    std::string delimiter = " ";
    std::string type = command.substr(0,command.find(delimiter));
    PlayableCharacter* player = map->getPlayer(username);
    if(type == "oro") {
        std::string gold = command.substr( element.find(delimiter));
        int gold_amount = std::stoi(gold);
        map->depositInBank(player,Position(x,y),gold_amount);
    } else {
        map->depositInBank(player,Position(x,y),element);
    }

}
