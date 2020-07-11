#include "SpawnCityCharactersMessageSerializer.h"

std::string SpawnCityCharactersMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    std::vector<spawn_character_t>data = message->getSpawnData();
    packer.pack(data);
    std::string result(ss.str());
    return result;
}

Message *SpawnCityCharactersMessageSerializer::deserialize(unsigned char *data,uint16_t len_data) {
    std::vector<spawn_character_t> characters;
    msgpack::object_handle oh =
            msgpack::unpack(reinterpret_cast<const char *>(data), len_data);

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();

    characters = deserialized.as<std::vector<spawn_character_t>>();

    return new SpawnCityCharacters(characters);
}
