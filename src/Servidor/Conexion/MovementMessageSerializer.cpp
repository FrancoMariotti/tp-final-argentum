#include <msgpack/adaptor/msgpack_tuple.hpp>
#include <msgpack.hpp>
#include "MovementMessageSerializer.h"

std::string MovementMessageSerializer::serialize(Message* message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    msgpack::type::tuple<int, int> src(message->getPlayerVelX(),
                                       message->getPlayerVelY());
    packer.pack(src);
    std::string result(ss.str());
    return result;
}

Message *MovementMessageSerializer::deserialize(unsigned char *data,uint16_t len_data) {
    // deserialize the buffer into msgpack::object instance.
    msgpack::object_handle oh =
            msgpack::unpack((const char *)(data), len_data);

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    msgpack::type::tuple<int, int> dst;
    deserialized.convert(dst);

    int x = std::get<0>(dst);
    int y = std::get<1>(dst);
    return new Movement(x,y);
}
