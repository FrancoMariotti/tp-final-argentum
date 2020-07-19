#include "SpawnPcMessageSerializer.h"

std::string SpawnPcMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    std::vector<spawn_playable_character_t> spawns = message->getPcSpawnData();
    packer.pack(spawns);
    std::string result(ss.str());
    return result;
}

Message *SpawnPcMessageSerializer::deserialize(unsigned char *data, uint32_t len_data) {
    msgpack::object_handle oh =
            msgpack::unpack(reinterpret_cast<const char *>(data), len_data);

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();

    std::vector<spawn_playable_character_t> spawns =
                            deserialized.as<std::vector<spawn_playable_character_t>>();

    return new SpawnPc(spawns);
}
