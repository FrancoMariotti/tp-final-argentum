//
// Created by franco on 7/7/20.
//

#include <msgpack.hpp>
#include "InventoryUpdateMessageSerializer.h"

char *InventoryUpdateMessageSerializer::serialize(Message *message) {
    msgpack::type::tuple<std::vector<std::string>> src(message->getItems());
    std::stringstream buffer;
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, src);
    // send the buffer ...
    buffer.seekg(0);
    return sbuf.data();
}

Message *InventoryUpdateMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    msgpack::object_handle oh =
            msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    msgpack::type::tuple<std::vector<std::string>> dst;
    deserialized.convert(dst);

    std::vector<std::string> items = std::get<0>(dst);
    return new InventoryUpdate(items);
}
