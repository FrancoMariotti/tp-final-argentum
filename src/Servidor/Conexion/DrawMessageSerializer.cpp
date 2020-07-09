#include <msgpack.hpp>
#include "stdio.h"
#include "stdlib.h"
#include <sstream>
#include "DrawMessageSerializer.h"

char* DrawMessageSerializer::serialize(Message *message) {
    msgpack::type::tuple<std::string,int, int,std::vector<int>> src(message->getLayerName(),
            message->getWidth(),message->getHeight(),message->getData());
    std::stringstream buffer;
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, src);
    // send the buffer ...
    buffer.seekg(0);
    return sbuf.data();
}

Message *DrawMessageSerializer::deserialize(char *data) {
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);


    // deserialized object is valid during the msgpack::object_handle instance is alive.
    /*msgpack::object deserialized = oh.get();
    // convert msgpack::object instance into the original type.
    // if the type is mismatched, it throws msgpack::type_error exception.
    msgpack::type::tuple<std::string,int, int,std::vector<int>> dst;
    deserialized.convert(dst);*/

    /*std::string layerName = ;
    int width = std::get<1>(dst);
    int height = std::get<2>(dst);
    std::vector<int> layer = std::get<3>(dst);*/

    //msgpack::object_handle oh =
     //       msgpack::unpack(data, strlen(data));

    //Draw *draw = new Draw();
    //oh->convert(*draw);


    msgpack::unpacker pac;

    pac.reserve_buffer(str.size());

    memcpy(pac.buffer(), str.data(), str.size());
    pac.buffer_consumed(str.size());

    // deserialize it.
    msgpack::object_handle msg;
    pac.next(msg);

    msgpack::object obj = msg.get();

    msgpack::type::tuple<std::string,int, int,std::vector<int>> dst =
            obj.as<msgpack::type::tuple<std::string,int, int,std::vector<int>>>();

    std::string layerName = std::get<0>(dst);
    int width = std::get<1>(dst);
    int height =std::get<2>(dst);
    std::vector<int>layerData = std::get<3>(dst);

//    Draw *draw = new Draw();


    return new Draw(layerName,layerData,width,height);
}
