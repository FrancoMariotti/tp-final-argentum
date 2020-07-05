//
// Created by franco on 4/7/20.
//

#include "ExtractCommand.h"
#include "PlayableCharacter.h"

ExtractCommand::ExtractCommand(Map *map):map(map) {}

void ExtractCommand::execute(std::string username, std::string params, int x, int y) {
    std::string delimiter = " ";
    std::string type = params.substr(0,params.find(delimiter));
    PlayableCharacter* player = map->getPlayer(username);
    Banker *banker = map->getBankerAtPosition(Position(x,y));

    if(type == "oro") {
        std::string gold = params.substr( params.find(delimiter));
        int gold_amount = std::stoi(gold);
        player->extract(gold_amount,banker);
    } else {
        player->extract(params,banker);
    }
}