//
// Created by franco on 2/7/20.
//

#include <iostream>
#include "DepositCommand.h"
#include "PlayableCharacter.h"

DepositCommand::DepositCommand(Map *map): map(map){}

void DepositCommand::execute(std::string username,std::string params,int x,int y) {
    std::string delimiter = " ";
    std::string type = params.substr(0,params.find(delimiter));
    PlayableCharacter* player = map->getPlayer(username);
    if(type == "oro") {
        std::string gold = params.substr( params.find(delimiter));
        //aca faltaria manejar la excepcion
        int gold_amount = std::stoi(gold);
        map->depositInBank(player,Position(x,y),gold_amount);
    } else {
        map->depositInBank(player,Position(x,y),params);
    }

}
