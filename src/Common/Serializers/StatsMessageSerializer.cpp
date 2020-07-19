#include "StatsMessageSerializer.h"

std::string StatsMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    packer.pack(message->getStats());
    std::string result(ss.str());
    return result;
}

Message *StatsMessageSerializer::deserialize(unsigned char *data, uint32_t len_data) {
    // deserialize the buffer into msgpack::object instance.
    msgpack::object_handle oh =
            msgpack::unpack((const char *)(data), len_data);

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    t_stats stats = deserialized.as<t_stats>();
    return new Stats(stats.health_percentage,
                    stats.mana_percentage,
                    stats.exp_percentage,
                    stats.gold,
                    stats.level);
}
