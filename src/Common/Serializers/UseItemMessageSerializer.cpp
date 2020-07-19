//
// Created by franco on 16/7/20.
//

#include "UseItemMessageSerializer.h"

std::string UseItemMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    packer.pack(message->getIndex());
    std::string result(ss.str());
    return result;
}

Message * UseItemMessageSerializer::deserialize(unsigned char *data, uint32_t len_data) {
    msgpack::object_handle oh =
            msgpack::unpack(reinterpret_cast<const char *>(data), len_data);

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();

    int index =
            deserialized.as<int>();

    return new UseItem(index);
}