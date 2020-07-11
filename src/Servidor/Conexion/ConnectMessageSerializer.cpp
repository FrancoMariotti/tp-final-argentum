#include <msgpack.hpp>
#include <Proxy/src/common_socket.h>
#include "ConnectMessageSerializer.h"

std::string ConnectMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    packer.pack(message->getConnectData());
    std::string result(ss.str());
    return result;
}

Message *ConnectMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    msgpack::object_handle oh =
            msgpack::unpack(str.data(), str.length());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    connect_t message = deserialized.as<connect_t>();

    return new Connect(message.username,message.charRace,message.charClass);
}
