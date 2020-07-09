//
// Created by franco on 7/7/20.
//

#include <msgpack.hpp>
#include "StatsUpdateMessageSerializer.h"

char* StatsUpdateMessageSerializer::serialize(Message *message) {
    t_stats stats = message->getStats();
    std::stringstream buffer;
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, stats);
    // send the buffer ...
    buffer.seekg(0);
    return sbuf.data();
}

Message *StatsUpdateMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    msgpack::object_handle oh =
            msgpack::unpack(str.data(), str.size());

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
