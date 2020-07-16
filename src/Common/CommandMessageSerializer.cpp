#include "CommandMessageSerializer.h"

std::string CommandMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    packer.pack(message->getCommand());
    std::string result(ss.str());
    return result;
}

Message *CommandMessageSerializer::deserialize(unsigned char *data, uint32_t len_data) {
    // deserialize the buffer into msgpack::object instance.
    //std::string str(data,len_data);

    msgpack::object_handle oh =
            msgpack::unpack(reinterpret_cast<const char *>(data), len_data);

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    command_t command;
    command = deserialized.as<command_t>();

    return new ExecuteCommand(
            command.input,
            command.username,
            command.x,
            command.y);
}
