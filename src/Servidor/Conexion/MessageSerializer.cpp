#include "MessageSerializer.h"
#include "MovementMessageSerializer.h"
#include "Proxy/src/common_osexception.h"
#include "UseItemMessageSerializer.h"
#include "InventoryUpdateMessageSerializer.h"
#include "SpawnNpcMessageSerializer.h"
#include "StatsUpdateMessageSerializer.h"
#include "EquipmentUpdateMessageSerializer.h"
#include "PlayerAttackMessageSerializer.h"
#include "SpawnCityCharactersMessageSerializer.h"
#include "ConsoleOutputMessageSerializer.h"
#include "DrawMessageSerializer.h"
#include "CommandMessageSerializer.h"
#include "NpcMovementMessageSerializer.h"
#include "ConnectMessageSerializer.h"
#include "SpawnDropsMessageSerializer.h"

MessageSerializer::MessageSerializer() {
    serializers[DRAW_MESSAGE_ID] = new  DrawMessageSerializer();
    serializers[MOVEMENT_MESSAGE_ID] = new  MovementMessageSerializer();
    serializers[USE_ITEM_MESSAGE_ID] = new  UseItemMessageSerializer();
    serializers[COMMAND_MESSAGE_ID] = new  CommandMessageSerializer();
    serializers[INVENTORY_UPDATE_MESSAGE_ID] = new  InventoryUpdateMessageSerializer();
    serializers[SPAWN_NPC_MESSAGE_ID] = new  SpawnNpcMessageSerializer();
    serializers[STATS_UPDATE_MESSAGE_ID] = new  StatsUpdateMessageSerializer();
    serializers[NPC_MOVEMENT_UPDATE_MESSAGE_ID] = new  NpcMovementMessageSerializer();
    serializers[EQUIPMENT_UPDATE_MESSAGE_ID] = new  EquipmentUpdateMessageSerializer();
    serializers[PLAYER_ATTACK_MESSAGE_ID] = new  PlayerAttackMessageSerializer();
    serializers[SPAWN_CITY_CHARACTERS_MESSAGE_ID] = new  SpawnCityCharactersMessageSerializer();
    serializers[SPAWN_DROPS_MESSAGE_ID] = new  SpawnDropsMessageSerializer();
    serializers[CONSOLE_OUTPUT_MESSAGE_ID] = new  ConsoleOutputMessageSerializer();
    serializers[CONNECT_MESSAGE_ID] = new  ConnectMessageSerializer();
}

std::string MessageSerializer::serialize(Message* message) {
    auto itr = serializers.find(message->getId());

    if(itr != serializers.end()) {
        return serializers.at(message->getId())->serialize(message);
    }

    throw OSError("Id de mensaje inexistente");
}

Message *MessageSerializer::deserialize(int messageId, char *data) {
    auto itr = serializers.find(messageId);
    if(itr == serializers.end()) return nullptr;
    return serializers.at(messageId)->deserialize(data);
}

MessageSerializer::~MessageSerializer() {
    auto itr = serializers.begin();
    for (; itr!=serializers.end() ; itr++) {
        delete itr->second;
    }
}


