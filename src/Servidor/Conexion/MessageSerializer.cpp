#include "MessageSerializer.h"
#include "MovementMessageSerializer.h"
#include "Proxy/src/common_osexception.h"

MessageSerializer::MessageSerializer() {
    serializers[MOVEMENT_MESSAGE_ID] = new  MovementMessageSerializer();
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


