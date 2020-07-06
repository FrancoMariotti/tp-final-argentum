#ifndef ARGENTUM_MESSAGESERIALIZER_H
#define ARGENTUM_MESSAGESERIALIZER_H
#include "map"
#include "Serializer.h"

class Message;

class MessageSerializer {
    std::map<int,Serializer*> serializers;
public:
    MessageSerializer();
    std::string serialize(Message* message);
    Message* deserialize(int messageId,char * data);
    ~MessageSerializer();
};


#endif //ARGENTUM_MESSAGESERIALIZER_H
