//
// Created by franco on 20/7/20.
//

#include "DisconnectMessageSerializer.h"

std::string DisconnectMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    packer.pack(message->getUsername());
    std::string result(ss.str());
    return result;
}

Message *DisconnectMessageSerializer::deserialize(unsigned char *data, uint32_t len_data) {
    msgpack::object_handle oh =
            msgpack::unpack(reinterpret_cast<const char *>(data), len_data);

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();

    std::string username = deserialized.as<std::string>();

    return new Disconnect(username);
}
