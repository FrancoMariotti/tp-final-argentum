//
// Created by franco on 19/7/20.
//

#include "MeditateCommand.h"
#include "Server/Model/Character/PlayableCharacter.h"

MeditateCommand::MeditateCommand(Map *map) : map(map) {}

void MeditateCommand::execute(std::string username, std::string params, int x, int y) {
    PlayableCharacter* character = map->getPlayer(username);
    if (character) {
        character->meditate();
    }
}

