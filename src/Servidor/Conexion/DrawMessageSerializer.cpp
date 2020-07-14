#include <Common/Socket.h>
#include "DrawMessageSerializer.h"
#include "msgpack/pack.hpp"
std::string DrawMessageSerializer::serialize(Message *message) {
    std::stringstream ss;

    msgpack::type::tuple<std::string,int, int,std::vector<int>> src(message->getLayerName(),
                                                                    message->getWidth(),
                                                                    message->getHeight(),
                                                                    message->getData());

    msgpack::packer<std::stringstream> packer(ss);
    packer.pack(src);
    std::string result(ss.str());
    return result;
}

Message *DrawMessageSerializer::deserialize(unsigned char *data,uint16_t len_data) {
    // deserialize the buffer into msgpack::object instance.
    msgpack::object_handle oh =
            msgpack::unpack(reinterpret_cast<const char *>(data), len_data);

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();

    msgpack::type::tuple<std::string,int, int,std::vector<int>> dst;
    deserialized.convert(dst);

    std::string layerName = std::get<0>(dst);
    int width = std::get<1>(dst);
    int height = std::get<2>(dst);
    std::vector<int> layer = std::get<3>(dst);

    return new Draw(layerName,layer,width,height);
}
