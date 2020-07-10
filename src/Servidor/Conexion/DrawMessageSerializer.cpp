#include <Proxy/src/common_socket.h>
#include "DrawMessageSerializer.h"
#include "msgpack/pack.hpp"
void DrawMessageSerializer::serialize(Socket& socket, Message *message) {
    /*msgpack::sbuffer temp_sbuffer;
    msgpack::packer<msgpack::sbuffer> packer(&temp_sbuffer);

    packer.pack_v4raw(message->getLayerName().size());  // Indicate that you are packing 5 raw bytes
    packer.pack_v4raw_body(message->getLayerName().data(), message->getLayerName().size()); // Pack the 5 b

    packer.pack_v4raw(sizeof(int));  // Indicate that you are packing 5 raw bytes
    int width = message->getWidth();
    packer.pack_v4raw_body((const char*)&width, sizeof(int)); // Pack the 5 b

    packer.pack_v4raw(sizeof(int));  // Indicate that you are packing 5 raw bytes
    int height = message->getWidth();
    packer.pack_v4raw_body((const char*)&height, sizeof(int)); // Pack the 5 b

    packer.pack_v4raw();*/
    /*std::stringstream layer;
    msgpack::packer<std::stringstream> packer(layer);

    packer.pack(message->getLayerName());
    //std::vector<int> data =message->getData();
    packer.pack(message->getData());
    auto itr = data.begin();
    for(;itr!=data.end();itr++) {
        packer.pack_str(*itr);
    }*/

    /*packer.pack_int(message->getWidth());
    packer.pack_int(message->getHeight());

    uint16_t length = htons(layer.str().size());
    socket.send((char*)&length, sizeof(uint16_t));

    socket.send(layer.str().data(),layer.str().size());*/

    std::stringstream buffer;
    /*Draw draw(message->getLayerName(),message->getData(),message->getWidth(),message->getHeight());
    msgpack::pack(buffer,draw);*/
    msgpack::packer<std::stringstream> pck(buffer);
    pck.pack(message->getLayerName());
    pck.pack_int(message->getWidth());
    pck.pack_int(message->getHeight());

    std::vector<int> data =message->getData();
    pck.pack_array(data.size());
    auto itr = data.begin();
    for(;itr!=data.end();itr++) {
        pck.pack_int64(*itr);
    }
    //msgpack::pack(buffer,message->getData());
    //msgpack::pack(buffer,message->getData());

    /*std::vector<int> data =message->getData();
    //packer.pack(message->getData());
    auto itr = data.begin();
    for(;itr!=data.end();itr++) {
        msgpack::pack(buffer,*itr);
    }*/

    uint16_t length = htons(buffer.str().size());
    socket.send((char*)&length, sizeof(uint16_t));
    socket.send(buffer.str().data(),buffer.str().size());
}

Message *DrawMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    //msgpack::object_handle oh =
     //       msgpack::unpack(str.data(), str.size());
    // deserialized object is valid during the msgpack::object_handle instance is alive.
    //msgpack::object deserialized = oh.get();

    /*msgpack::unpacker pac;
    pac.reserve_buffer( str.size() );
    std::copy( str.begin(), str.end(), pac.buffer() );
    pac.buffer_consumed( str.size() );

    msgpack::object_handle oh;
    pac.next(oh);
    std::string layerName = oh.get().as<std::string>();
    pac.next(oh);

    auto layerData = oh.get().as<std::vector<int>>();*/


    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.

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
    //std::vector<int> layerData;
    std::vector<int> layerAux = oh.get().as<std::vector<int>>();


    return new Draw(layerName,layerAux,width,height);
}
