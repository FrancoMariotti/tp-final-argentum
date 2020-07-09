#include "ConsoleOutputMessageSerializer.h"
#include <msgpack/adaptor/msgpack_tuple.hpp>
#include <msgpack.hpp>

char* ConsoleOutputMessageSerializer::serialize(Message *message) {
    msgpack::type::tuple<std::vector<std::string>> src(message->getConsoleOutput());
    std::stringstream buffer;
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, src);
    // send the buffer ...
    buffer.seekg(0);
    return sbuf.data();
}

Message *ConsoleOutputMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    msgpack::object_handle oh =
            msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    msgpack::type::tuple<std::vector<std::string>> dst;
    deserialized.convert(dst);

    std::vector<std::string> output = std::get<0>(dst);
    return new ConsoleOutput(output);
}
