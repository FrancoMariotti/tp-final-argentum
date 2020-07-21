//
// Created by agustin on 19/7/20.
//

#include "client_update.h"
#include "client_gui.h"


void InitStaticNPC::execute(GUI &gui, std::unique_ptr<Message> msg) const {
    gui.initStaticRenderables(msg->getSpawnData());
}

void UpdatePlayerPos::execute(GUI &gui, std::unique_ptr<Message> msg) const {
    location_t  location = msg->getLocation();
    gui.updatePlayerPos(location.id,location.x, location.y);
}

void UpdateInventory::execute(GUI &gui, std::unique_ptr<Message> msg) const {
    gui.updateInventory(msg->getItems());
}

void UpdateStats::execute(GUI &gui, std::unique_ptr<Message> msg) const {
    gui.updatePlayerStats(msg->getStats());
}

void UpdateNPCs::execute(GUI &gui, std::unique_ptr<Message> msg) const {
    gui.updateRenderables(msg->getSpawnData());
}

void UpdateDrops::execute(GUI &gui, std::unique_ptr<Message> msg) const {
    gui.updateDrops(msg->getSpawnData());
}

void UpdateNPCPos::execute(GUI &gui, std::unique_ptr<Message> msg) const {
    location_t movement = msg->getLocation();
    gui.updateRenderablePos(movement.x, movement.y, movement.id);
}

void UpdateConsole::execute(GUI &gui, std::unique_ptr<Message> msg) const {
    gui.updateConsoleOutput(msg->getConsoleOutput());
}

void UpdateEquipment::execute(GUI &gui, std::unique_ptr<Message> msg) const {
    equipment_t equipment = msg->getEquipment();
    gui.updateRenderablePlayableEquipment(equipment,equipment.username);
}

void UpdatePlayers::execute(GUI &gui, std::unique_ptr<Message> msg) const {
    gui.updateRenderablePlayables(msg->getPcSpawnData());
}

