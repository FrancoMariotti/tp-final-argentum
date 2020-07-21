//
// Created by agustin on 19/7/20.
//

#include <Common/OsException.h>
#include "client_update_factory.h"

UpdateFactory::UpdateFactory() {
    this->updates.insert(std::make_pair(MOVEMENT_MESSAGE_ID, new UpdatePlayerPos));
    this->updates.insert(std::make_pair(STATS_UPDATE_MESSAGE_ID, new UpdateStats));
    this->updates.insert(std::make_pair(INVENTORY_UPDATE_MESSAGE_ID, new UpdateInventory));
    this->updates.insert(std::make_pair(SPAWN_NPC_MESSAGE_ID, new UpdateNPCs));
    this->updates.insert(std::make_pair(SPAWN_DROPS_MESSAGE_ID, new UpdateDrops));
    this->updates.insert(std::make_pair(NPC_MOVEMENT_UPDATE_MESSAGE_ID, new UpdateNPCPos));
    this->updates.insert(std::make_pair(CONSOLE_OUTPUT_MESSAGE_ID, new UpdateConsole));
    this->updates.insert(std::make_pair(EQUIPMENT_UPDATE_MESSAGE_ID, new UpdateEquipment));
    this->updates.insert(std::make_pair(SPAWN_PC_MESSAGE_ID, new UpdatePlayers));
}

const Update *UpdateFactory::getUpdate(const int msg_id) const{
    if(updates.find(msg_id) != updates.end()){
        return updates.at(msg_id);
    }
    throw OSError("Message ID No es un update del factory, Message_ID: %d", msg_id);
}

UpdateFactory::~UpdateFactory() {
    auto it = updates.begin();
    while (it != updates.end()) {
        delete (it->second);
        it = updates.erase(it);
    }
}
