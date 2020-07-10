#include <Proxy/src/common_socket.h>
#include "MessageSerializer.h"
#include "Proxy/src/common_osexception.h"
#include "MovementMessageSerializer.h"
#include "DrawMessageSerializer.h"
#include "ConnectMessageSerializer.h"

MessageSerializer::MessageSerializer() {
    serializers[DRAW_MESSAGE_ID] = new  DrawMessageSerializer();
    serializers[CONNECT_MESSAGE_ID] = new  ConnectMessageSerializer();
}

void MessageSerializer::serialize(Socket& socket,Message* message) {
    auto itr = serializers.find(message->getId());

    if(itr != serializers.end()) {
        serializers.at(message->getId())->serialize(socket,message);
    } else {
        throw OSError("Id de mensaje inexistente");
    }
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



