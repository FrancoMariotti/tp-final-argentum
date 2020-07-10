#ifndef ARGENTUM_MESSAGESERIALIZER_H
#define ARGENTUM_MESSAGESERIALIZER_H
#include "map"
#include "Serializer.h"
#include "Proxy/src/common_socket.h"

class Message;

class MessageSerializer {
    std::map<int,Serializer*> serializers;
public:
    MessageSerializer();
    void serialize(Socket& socket,Message* message);
    Message* deserialize(int messageId,char * data);
    ~MessageSerializer();
};


#endif //ARGENTUM_MESSAGESERIALIZER_H
