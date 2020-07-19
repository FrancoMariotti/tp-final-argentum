#include "EquipmentMessageSerializer.h"

std::string EquipmentMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    packer.pack(message->getEquipment());
    std::string result(ss.str());
    return result;
}

Message * EquipmentMessageSerializer::deserialize(unsigned char *data, uint32_t len_data) {
    // deserialize the buffer into msgpack::object instance.
    msgpack::object_handle oh =
            msgpack::unpack((const char *)(data), len_data);

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    equipment_t equipment = deserialized.as<equipment_t>();
    return new EquipmentUpdate(equipment.username,
                                equipment.weaponName,
                                equipment.armourName,
                                equipment.shieldName,
                                equipment.helmetName);
}
