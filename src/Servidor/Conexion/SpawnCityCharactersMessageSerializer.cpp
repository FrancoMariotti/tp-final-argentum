#include "SpawnCityCharactersMessageSerializer.h"

std::string SpawnCityCharactersMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    std::vector<spawn_character_t>data = message->getSpawnData();
    auto itr = data.begin();
    packer.pack(data.size());
    for(;itr!=data.end();itr++) {
        packer.pack(std::to_string(itr->x));
        packer.pack(std::to_string(itr->y));
        packer.pack(itr->id);
    }
    std::string result(ss.str());
    return result;
}

Message *SpawnCityCharactersMessageSerializer::deserialize(char *data) {
    std::string str(data);

    msgpack::unpacker pac;
    pac.reserve_buffer( str.size() );
    std::copy( str.begin(), str.end(), pac.buffer() );
    pac.buffer_consumed( str.size() );
    std::vector<spawn_character_t> characters;
    msgpack::object_handle oh;
    pac.next(oh);
    int sizeArray = oh.get().as<int>();
    pac.next(oh);
    for(int i = 0; i < sizeArray; i++) {
        spawn_character_t character;
        character.x = std::stoi(oh.get().as<std::string>());
        pac.next(oh);
        character.y = std::stoi(oh.get().as<std::string>());
        pac.next(oh);
        character.id = oh.get().as<std::string>();
        pac.next(oh);
        characters.push_back(std::move(character));
    }
    return new SpawnCityCharacters(characters);
}
