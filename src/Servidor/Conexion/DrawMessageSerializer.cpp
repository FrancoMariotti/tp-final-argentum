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
    std::vector<int> data =message->getData();
    auto itr = data.begin();
    std::stringstream layer;
    msgpack::packer<std::stringstream> packer(layer);

    packer.pack(message->getLayerName());
    for(;itr!=data.end();itr++) {
        packer.pack_str(*itr);
    }

    packer.pack_int(message->getWidth());
    packer.pack_int(message->getHeight());

    uint16_t length = htons(layer.str().size());
    socket.send((char*)&length, sizeof(uint16_t));

    socket.send(layer.str().data(),layer.str().size());

    /*std::stringstream buffer;
    Draw draw(message->getLayerName(),message->getData(),message->getWidth(),message->getHeight());
    msgpack::pack(buffer,draw);

    uint16_t length = htons(buffer.str().size());
    socket.send((char*)&length, sizeof(uint16_t));
    socket.send(buffer.str().data(),buffer.str().size());*/
}

Message *DrawMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    //msgpack::object_handle oh =
     //       msgpack::unpack(str.data(), str.size());
    // deserialized object is valid during the msgpack::object_handle instance is alive.
    //msgpack::object deserialized = oh.get();

    msgpack::unpacker pac;
    pac.reserve_buffer( str.size() );
    std::copy( str.begin(), str.end(), pac.buffer() );
    pac.buffer_consumed( str.size() );

    msgpack::object_handle oh;
    while ( pac.next(oh) ) {
        msgpack::object msg = oh.get();
        std::cout << msg << std::endl;
    }


    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.

    //Draw draw;

    //deserialized.convert(draw);

    return new Draw();
}
