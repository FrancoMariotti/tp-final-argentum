#include <msgpack.hpp>
#include <Proxy/src/common_socket.h>
#include "ConnectMessageSerializer.h"

void ConnectMessageSerializer::serialize(Socket& socket,Message *message) {
    msgpack::sbuffer temp_sbuffer;
    msgpack::packer<msgpack::sbuffer> packer(&temp_sbuffer);
    packer.pack(message->getConnectData());
    uint16_t length = htons(temp_sbuffer.size());
    socket.send((char*)&length, sizeof(uint16_t));
    socket.send(temp_sbuffer.data(),temp_sbuffer.size());
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
