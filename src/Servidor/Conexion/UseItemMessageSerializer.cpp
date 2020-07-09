#include <msgpack.hpp>
#include "UseItemMessageSerializer.h"

std::string UseItemMessageSerializer::serialize(Message *message) {
    msgpack::type::tuple<int> src(message->getIndex());
    std::stringstream buffer;
    msgpack::pack(buffer, src);
    // send the buffer ...
    buffer.seekg(0);
    return buffer.str();
}

Message *UseItemMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    msgpack::object_handle oh =
            msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    msgpack::type::tuple<int> dst;
    deserialized.convert(dst);

    int index = std::get<0>(dst);
    return new UseItem(index);
}
