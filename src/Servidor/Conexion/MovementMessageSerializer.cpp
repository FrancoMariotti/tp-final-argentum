#include <msgpack/adaptor/msgpack_tuple.hpp>
#include <msgpack.hpp>
#include "MovementMessageSerializer.h"

std::string MovementMessageSerializer::serialize(Message* message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    location_t location = message->getLocation();
    packer.pack(location);
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
    location_t location = deserialized.as<location_t>();
    return new Movement(location.id,location.x,location.y);
}
