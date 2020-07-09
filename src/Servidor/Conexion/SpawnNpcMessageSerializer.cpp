#include <msgpack.hpp>
#include "SpawnNpcMessageSerializer.h"
#include "Proxy/src/common_message_structs.h"


char* SpawnNpcMessageSerializer::serialize(Message *message) {
    std::vector<spawn_character_t> src = message->getSpawnData();
    std::stringstream buffer;
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, src);
    // send the buffer ...
    buffer.seekg(0);
    return sbuf.data();
}

Message *SpawnNpcMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    msgpack::object_handle oh =
            msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    std::vector<spawn_character_t> dst;
    deserialized.convert(dst);
    return new SpawnNpc(dst);
}
