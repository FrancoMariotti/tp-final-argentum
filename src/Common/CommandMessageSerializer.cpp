#include "CommandMessageSerializer.h"

std::string CommandMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    msgpack::type::tuple<std::string,int,int> src(message->getCommand(),
                                            message->getX(),
                                            message->getY());
    packer.pack(src);
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
    msgpack::type::tuple<std::string,int,int> dst;
    dst = deserialized.as<msgpack::type::tuple<std::string,int,int>>();

    return new ExecuteCommand(
            std::get<0>(dst),
            std::get<1>(dst),
            std::get<2>(dst));
}
