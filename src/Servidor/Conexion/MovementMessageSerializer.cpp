#include <msgpack/adaptor/msgpack_tuple.hpp>
#include <msgpack.hpp>
#include "MovementMessageSerializer.h"

std::string MovementMessageSerializer::serialize(Message* message) {
    msgpack::type::tuple<int, int> src(message->getX(),
                                       message->getY());
    std::stringstream buffer;
    msgpack::pack(buffer, src);
    // send the buffer ...
    buffer.seekg(0);
    return buffer.str();
}

Message *MovementMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    msgpack::object_handle oh =
            msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    msgpack::type::tuple<int, int, int> dst;
    deserialized.convert(dst);

    int x = std::get<0>(dst);
    int y = std::get<1>(dst);
    return new Movement(x,y);
}
