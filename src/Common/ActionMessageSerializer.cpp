#include "ActionMessageSerializer.h"

std::string ActionMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    msgpack::type::tuple<int,location_t> src(message->getId(),
                                                          message->getLocation());
    packer.pack(src);
    std::string result(ss.str());
    return result;
}

Message * ActionMessageSerializer::deserialize(unsigned char *data, uint32_t len_data) {
    msgpack::object_handle oh =
            msgpack::unpack(reinterpret_cast<const char *>(data), len_data);

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();

    msgpack::type::tuple<int,location_t> dst;
    deserialized.convert(dst);
    int id = std::get<0>(dst);
    location_t location = std::get<1>(dst);

    return new ActionUpdate(id,
                            location.id,
                            location.x,
                            location.y);
}
