#include <msgpack/adaptor/msgpack_tuple.hpp>
#include <msgpack.hpp>
#include "PlayerAttackMessageSerializer.h"

std::string PlayerAttackMessageSerializer::serialize(Message *message) {
    t_player_attack attack = message->getAttack();
    msgpack::type::tuple<std::string,int, int> src(attack.username,
                                       attack.enemy_x,
                                       attack.enemy_y);
    std::stringstream buffer;
    msgpack::pack(buffer, src);
    // send the buffer ...
    buffer.seekg(0);
    return buffer.str();
}

Message *PlayerAttackMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    msgpack::object_handle oh =
            msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    msgpack::type::tuple<std::string, int, int> dst;
    deserialized.convert(dst);

    std::string username = std::get<0>(dst);
    int x = std::get<1>(dst);
    int y = std::get<1>(dst);
    return new Attack(username,x,y);
}
