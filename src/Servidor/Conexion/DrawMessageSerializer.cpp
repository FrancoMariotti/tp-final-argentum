#include <sstream>
#include <Proxy/src/common_socket.h>
#include "DrawMessageSerializer.h"

void DrawMessageSerializer::serialize(Socket& socket,Message *message) {
    msgpack::sbuffer temp_sbuffer;
    msgpack::packer<msgpack::sbuffer> packer(&temp_sbuffer);
    std::vector<int>data = message->getData();
    packer.pack_v4raw(message->getLayerName().size());
    packer.pack_v4raw_body(message->getLayerName().data(),message->getLayerName().size());
    //packer.pack(message->getLayerName());
    packer.pack_v4raw(sizeof(int));
    int width = message->getWidth();
    packer.pack_v4raw_body((const char*)&width,sizeof(int));
    packer.pack_v4raw(sizeof(int));
    int height = message->getHeight();
    packer.pack_v4raw_body((const char*)&height,sizeof(int));
    //packer.pack(message->getWidth());
    //packer.pack(message->getHeight());
    packer.pack_array(data.size());
    auto itr = data.begin();
    for(;itr!= data.end();itr++) {
        //packer.pack_long(*itr);
        //packer.pack_v4raw(sizeof(int));
        packer.pack_int(*itr);
    }


    uint16_t length = htons(temp_sbuffer.size());
    socket.send((char*)&length, sizeof(uint16_t));
    socket.send(temp_sbuffer.release(),temp_sbuffer.size());
}

Message *DrawMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);


    msgpack::object_handle oh =
            msgpack::unpack(data, strlen(data));
    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    //msgpack::type::tuple<std::string,int, int,std::vector<int>> dst;
    //deserialized.convert(dst);

    //std::string layerName =  std::get<0>(dst);
    //int width = std::get<1>(dst);
    //int height = std::get<2>(dst);
    //std::vector<int> layerData = std::get<3>(dst);
    Draw draw;

    deserialized.convert(draw);

    return new Draw(draw);
}
