//
// Created by franco on 18/7/20.
//

#include "LoginMessageSerializer.h"

std::string LoginMessageSerializer::serialize(Message *message) {
    std::stringstream ss;
    msgpack::packer<std::stringstream> packer(ss);
    packer.pack(message->getLoginData());
    std::string result(ss.str());
    return result;
}

Message *LoginMessageSerializer::deserialize(unsigned char *data, uint32_t len_data) {
    msgpack::object_handle oh =
            msgpack::unpack(reinterpret_cast<const char *>(data), len_data);

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    t_client_login login= deserialized.as<t_client_login>();

    return new Login(login.username,login.password,login.id);
}
