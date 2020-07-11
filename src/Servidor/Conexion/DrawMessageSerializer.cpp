#include <Proxy/src/common_socket.h>
#include "DrawMessageSerializer.h"
#include "msgpack/pack.hpp"
std::string DrawMessageSerializer::serialize(Message *message) {
    std::stringstream ss;

    msgpack::packer<std::stringstream> pck(ss);
    pck.pack(message->getLayerName());
    pck.pack(message->getWidth());
    pck.pack(message->getHeight());

    std::vector<int> data =message->getData();
    auto itr = data.begin();
    pck.pack_int(data.size());
    for(;itr!=data.end();itr++) {
        pck.pack(std::to_string(*itr));
    }
    std::string result(ss.str());
    return result;
}

Message *DrawMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);
    msgpack::unpacker pac;
    pac.reserve_buffer( str.size() );
    std::copy( str.begin(), str.end(), pac.buffer() );
    pac.buffer_consumed( str.size() );

    msgpack::object_handle oh;
    pac.next(oh);
    std::string layerName = oh.get().as<std::string>();
    pac.next(oh);
    int width = oh.get().as<int>();
    pac.next(oh);
    int height = oh.get().as<int>();
    pac.next(oh);
    int size_array = oh.get().as<int>();
    std::vector<int> layerData;
    for(int i = 0;i < size_array;i++) {
        pac.next(oh);
        std::string number;
        oh.get().convert(number);
        layerData.push_back(std::stoi(number));
    }

    return new Draw(layerName,layerData,width,height);
}
