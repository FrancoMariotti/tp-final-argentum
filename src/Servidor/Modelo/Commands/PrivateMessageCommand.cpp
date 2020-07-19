//
// Created by franco on 18/7/20.
//

#include "PrivateMessageCommand.h"
#include "Servidor/Modelo/Character/PlayableCharacter.h"

PrivateMessageCommand::PrivateMessageCommand(Map *map) : map(map) {}

void PrivateMessageCommand::execute(std::string username, std::string params, int x, int y) {
    std::string delimiter = " ";
    std::string receiverStr, message;
    receiverStr = params.substr(0, params.find(delimiter));
    message = params.substr(params.find(delimiter) + 1);
    PlayableCharacter* receiver = map->getPlayer(receiverStr);
    if (receiver) {
        receiver->receivePrivateMessageFrom(username, message);
    }
}


