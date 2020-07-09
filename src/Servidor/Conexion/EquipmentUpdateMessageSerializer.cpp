//
// Created by franco on 7/7/20.
//

#include <msgpack.hpp>
#include "EquipmentUpdateMessageSerializer.h"
#include "Proxy/src/common_message_structs.h"

std::string EquipmentUpdateMessageSerializer::serialize(Message *message) {
    equipment_t src = message->getEquipment();
    std::stringstream buffer;
    msgpack::pack(buffer, src);
    // send the buffer ...
    buffer.seekg(0);
    return buffer.str();
}

Message *EquipmentUpdateMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    msgpack::object_handle oh =
            msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.

    equipment_t equipment= deserialized.as<equipment_t>();

    return new EquipmentUpdate(equipment.weaponName,
                                equipment.armourName,
                                equipment.shieldName,
                                equipment.helmetName);
}
