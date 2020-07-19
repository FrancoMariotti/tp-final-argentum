#include "../Socket.h"
#include "MessageSerializer.h"
#include "../OsException.h"
#include "MovementMessageSerializer.h"
#include "DrawMessageSerializer.h"
#include "ConnectMessageSerializer.h"
#include "SpawnStaticObjectsMessageSerializer.h"
#include "SpawnPcMessageSerializer.h"
#include "StatsMessageSerializer.h"
#include "InventoryMessageSerializer.h"
#include "CommandMessageSerializer.h"
#include "ActionMessageSerializer.h"
#include "ConsoleOutputMessageSerializer.h"
#include "EquipmentMessageSerializer.h"
#include "UseItemMessageSerializer.h"
#include "LoginMessageSerializer.h"

MessageSerializer::MessageSerializer() {
    serializers.push_back(new  DrawMessageSerializer());
    serializers.push_back(new  ConnectMessageSerializer());
    serializers.push_back(new  SpawnStaticObjectsMessageSerializer());
    serializers.push_back(new  SpawnPcMessageSerializer());
    serializers.push_back(new  MovementMessageSerializer());
    serializers.push_back(new  StatsMessageSerializer());
    serializers.push_back(new  InventoryMessageSerializer());
    serializers.push_back(new  CommandMessageSerializer());
    serializers.push_back(new  ActionMessageSerializer());
    serializers.push_back(new  UseItemMessageSerializer());
    serializers.push_back(new  ConsoleOutputMessageSerializer());
    serializers.push_back(new  EquipmentMessageSerializer());
    serializers.push_back(new  LoginMessageSerializer());


    serializersTable[DRAW_MESSAGE_ID] = 0;
    serializersTable[CONNECT_MESSAGE_ID] = 1;
    serializersTable[SPAWN_CITY_CHARACTERS_MESSAGE_ID] = 2;
    serializersTable[SPAWN_DROPS_MESSAGE_ID] = 2;
    serializersTable[SPAWN_NPC_MESSAGE_ID] = 2;
    serializersTable[SPAWN_PC_MESSAGE_ID] = 3;
    serializersTable[MOVEMENT_MESSAGE_ID] = 4;
    serializersTable[STATS_UPDATE_MESSAGE_ID] = 5;
    serializersTable[INVENTORY_UPDATE_MESSAGE_ID] = 6;
    serializersTable[COMMAND_MESSAGE_ID] = 7;
    serializersTable[NPC_MOVEMENT_UPDATE_MESSAGE_ID] = 8;
    serializersTable[PLAYER_ATTACK_MESSAGE_ID] = 8;
    serializersTable[USE_ITEM_MESSAGE_ID] = 9;
    serializersTable[CONSOLE_OUTPUT_MESSAGE_ID] = 10;
    serializersTable[EQUIPMENT_UPDATE_MESSAGE_ID] = 11;
    serializersTable[LOGIN_MESSAGE_ID] = 12;
    serializersTable[SIGNUP_MESSAGE_ID] = 12;
}

std::string MessageSerializer::serialize(Message* message) {
    auto itr = serializersTable.find(message->getId());

    if(itr != serializersTable.end()) {
        return serializers[serializersTable.at(message->getId())]->serialize(message);
    }
    throw OSError("Id de mensaje inexistente");
}

Message *MessageSerializer::deserialize(int messageId,unsigned char *data,uint32_t len_data) {
    auto itr = serializersTable.find(messageId);
    if(itr == serializersTable.end())  return nullptr;
    return serializers[serializersTable.at(messageId)]->deserialize(data,len_data);
}

MessageSerializer::~MessageSerializer() {
    auto itr = serializers.begin();
    for (; itr!=serializers.end() ; itr++) {
        delete *itr;
    }
}



