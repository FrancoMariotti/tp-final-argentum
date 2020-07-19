#include "InventoryMessageSerializer.h"

std::string InventoryMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    packer.pack(message->getItems());
    std::string result(ss.str());
    return result;
}

Message *InventoryMessageSerializer::deserialize(unsigned char *data, uint32_t len_data) {
    msgpack::object_handle oh =
            msgpack::unpack(reinterpret_cast<const char *>(data), len_data);

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    std::vector<std::string> items = deserialized.as<std::vector<std::string>>();

    return new InventoryUpdate(items);
}
