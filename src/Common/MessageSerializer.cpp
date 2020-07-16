#include "Socket.h"
#include "MessageSerializer.h"
#include "OsException.h"
#include "MovementMessageSerializer.h"
#include "DrawMessageSerializer.h"
#include "ConnectMessageSerializer.h"
#include "SpawnStaticObjectMessageSerializer.h"
#include "SpawnPcMessageSerializer.h"
#include "StatsMessageSerializer.h"
#include "InventoryMessageSerializer.h"
#include "CommandMessageSerializer.h"

MessageSerializer::MessageSerializer() {
    serializers[DRAW_MESSAGE_ID] = new  DrawMessageSerializer();
    serializers[CONNECT_MESSAGE_ID] = new  ConnectMessageSerializer();
    serializers[SPAWN_CITY_CHARACTERS_MESSAGE_ID] = new  SpawnStaticObjectMessageSerializer();
    serializers[SPAWN_DROPS_MESSAGE_ID] = new  SpawnStaticObjectMessageSerializer();
    serializers[SPAWN_NPC_MESSAGE_ID] = new  SpawnStaticObjectMessageSerializer();
    serializers[SPAWN_PC_MESSAGE_ID] = new SpawnPcMessageSerializer();
    serializers[MOVEMENT_MESSAGE_ID] = new MovementMessageSerializer();
    serializers[STATS_UPDATE_MESSAGE_ID] = new StatsMessageSerializer();
    serializers[INVENTORY_UPDATE_MESSAGE_ID] = new InventoryMessageSerializer();
    serializers[COMMAND_MESSAGE_ID] = new CommandMessageSerializer();
}

std::string MessageSerializer::serialize(Message* message) {
    auto itr = serializers.find(message->getId());

    if(itr != serializers.end()) {
        return serializers.at(message->getId())->serialize(message);
    }
    throw OSError("Id de mensaje inexistente");
}

Message *MessageSerializer::deserialize(int messageId,unsigned char *data,uint32_t len_data) {
    auto itr = serializers.find(messageId);
    if(itr == serializers.end()) return nullptr;
    return serializers.at(messageId)->deserialize(data,len_data);
}

MessageSerializer::~MessageSerializer() {
    auto itr = serializers.begin();
    for (; itr!=serializers.end() ; itr++) {
        delete itr->second;
    }
}



