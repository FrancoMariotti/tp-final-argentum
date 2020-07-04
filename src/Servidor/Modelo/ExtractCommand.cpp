//
// Created by franco on 4/7/20.
//

#include "ExtractCommand.h"

ExtractCommand::ExtractCommand(Map *map):map(map) {}

void ExtractCommand::execute(std::string username, std::string command, int x, int y) {
    std::string element = command;
    std::string delimiter = " ";
    std::string type = command.substr(0,command.find(delimiter));
    PlayableCharacter* player = map->getPlayer(username);
    if(type == "oro") {
        std::string gold = command.substr( element.find(delimiter));
        int gold_amount = std::stoi(gold);
        map->extractFromBank(player,Position(x,y),gold_amount);
    } else {
        map->extractFromBank(player,Position(x,y),element);
    }
}