#include <msgpack.hpp>
#include "ConnectMessageSerializer.h"

std::string ConnectMessageSerializer::serialize(Message *message) {
    connect_t data = message->getConnectData();
    std::stringstream buffer;
    msgpack::pack(buffer, data);
    // send the buffer ...
    buffer.seekg(0);
    return buffer.str();
}

Message *ConnectMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    msgpack::object_handle oh =
            msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    connect_t message = deserialized.as<connect_t>();

    return new Connect(message.username,message.charRace,message.charClass);
}
