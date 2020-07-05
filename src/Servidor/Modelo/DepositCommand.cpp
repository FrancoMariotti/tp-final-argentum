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
    Banker* banker = map->getBankerAtPosition(Position(x,y));
    if(type == "oro") {
        std::string gold = params.substr( params.find(delimiter));
        //aca faltaria manejar la excepcion
        int gold_amount = std::stoi(gold);
        player->deposit(gold_amount,banker);
    } else {
        player->deposit(params,banker);
    }

}
