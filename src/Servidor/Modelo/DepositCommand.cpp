//
// Created by franco on 2/7/20.
//

#include <iostream>
#include "DepositCommand.h"
#include "PlayableCharacter.h"

DepositCommand::DepositCommand() = default;

void DepositCommand::execute(std::string username,std::string command,int x,int y) {
    //std::string element = command;
    std::cout << "Ejecucion comando Depositar" <<std::endl;
    std::cout << "command:" << command <<std::endl;
    std::cout << "y:" << x <<std::endl;
    std::cout << "x:" << y <<std::endl;
    /*PlayableCharacter * player = map->getPlayer(username);
    Banker* banker = map->getBankerAtPosition(x,y);
    if(banker) player->deposit(element,banker);*/
}
