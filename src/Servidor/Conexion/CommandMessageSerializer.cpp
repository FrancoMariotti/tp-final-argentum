//
// Created by franco on 7/7/20.
//

#include <msgpack.hpp>
#include "CommandMessageSerializer.h"

char* CommandMessageSerializer::serialize(Message *message) {
    msgpack::type::tuple<std::string,std::string,
                                    int,int> src(message->getUserName(),
                                                 message->getCommand(),
                                                 message->getX(),
                                                 message->getY());
    std::stringstream buffer;
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, src);
    // send the buffer ...
    buffer.seekg(0);
    return sbuf.data();
}

Message *CommandMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    msgpack::object_handle oh =
            msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    msgpack::type::tuple<std::string,std::string,int,int> dst;
    deserialized.convert(dst);

    std::string username = std::get<0>(dst);
    std::string command = std::get<1>(dst);
    int x = std::get<2>(dst);
    int y = std::get<3>(dst);
    return new ExecuteCommand(username,command,x,y);
}
