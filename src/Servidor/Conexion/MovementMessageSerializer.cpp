#include <msgpack/adaptor/msgpack_tuple.hpp>
#include <sstream>
#include "MovementMessageSerializer.h"

std::string MovementMessageSerializer::serialize(Message* message) {
    msgpack::type::tuple<int, int, int> src(message->getId(),
                                                    message->getX(),
                                                    message->getY());
    std::stringstream buffer;
    msgpack::pack(buffer, src);
    // send the buffer ...
    buffer.seekg(0);
    return buffer.str();
}

Message *MovementMessageSerializer::deserialize(char *data) {
    return nullptr;
}
