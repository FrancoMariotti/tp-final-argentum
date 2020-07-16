#include "ConsoleOutputMessageSerializer.h"

std::string ConsoleOutputMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    packer.pack(message->getConsoleOutput());
    std::string result(ss.str());
    return result;
}

Message * ConsoleOutputMessageSerializer::deserialize(unsigned char *data, uint32_t len_data) {
    msgpack::object_handle oh =
            msgpack::unpack(reinterpret_cast<const char *>(data), len_data);

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();

    std::vector<std::string> outputs =
            deserialized.as<std::vector<std::string>>();

    return new ConsoleOutput(outputs);
}