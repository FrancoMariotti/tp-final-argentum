#include <Proxy/src/common_socket.h>
#include "MessageSerializer.h"
#include "Proxy/src/common_osexception.h"

MessageSerializer::MessageSerializer() = default;

void MessageSerializer::serialize(Socket &socket,Message* message) {
    //std::stringstream buffer;

    msgpack::sbuffer buffer;

    if(message->getId() == DRAW_MESSAGE_ID) {
        uint16_t big_end = htons(DRAW_MESSAGE_ID);
        socket.send((char*)&big_end, sizeof(uint16_t));
        Draw draw(message->getLayerName(),message->getData(),message->getWidth(),message->getHeight());
        msgpack::pack(&buffer, draw);
        //msgpack::pack(buffer, draw);
    }
    if(message->getId() == CONNECT_MESSAGE_ID) {
        uint16_t big_end = htons(CONNECT_MESSAGE_ID);
        socket.send((char*)&big_end, sizeof(uint16_t));
        connect_t  connect = message->getConnectData();
        msgpack::pack(&buffer, connect);
        //msgpack::pack(buffer, connect);
    }
    // send the buffer ...
    //buffer.seekg(0);
    uint16_t big_end = htons(buffer.size());
    socket.send((char*)&big_end, sizeof(uint16_t));
    socket.send(buffer.data(),buffer.size());
}

Message *MessageSerializer::deserialize(int messageId, char *data) {
    std::string aux(data);
    // deserialize the buffer into msgpack::object instance.
    std::string str(data);

    msgpack::object_handle result =
            msgpack::unpack(str.data(), str.size());

    // deserialized object is valid during the msgpack::object_handle instance is alive.
    msgpack::object obj = result.get();

    if(messageId == DRAW_MESSAGE_ID) {

        Draw m2 = obj.as<Draw>();

        return new Draw(m2);
    } else if(messageId == CONNECT_MESSAGE_ID) {
        connect_t connect;
        obj.convert(connect);

        return new Connect(connect.username,connect.charRace,connect.charClass);
    }
    return nullptr;
}

MessageSerializer::~MessageSerializer() = default;


