#include <msgpack.hpp>
#include "NpcMovementMessageSerializer.h"
#include "Proxy/src/common_message_structs.h"

std::string NpcMovementMessageSerializer::serialize(Message *message) {
    npc_movement_t src = message->getMovement();
    std::stringstream buffer;
    msgpack::pack(buffer, src);
    // send the buffer ...
    buffer.seekg(0);
    return buffer.str();
}

Message *NpcMovementMessageSerializer::deserialize(char *data) {
    std::string str(data);

    msgpack::object_handle oh =
            msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.

    npc_movement_t movement = deserialized.as<npc_movement_t>();
    return new MovementNpcUpdate(movement.id,movement.x,movement.y);
}
