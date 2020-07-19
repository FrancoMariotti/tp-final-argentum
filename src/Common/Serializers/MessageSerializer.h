#ifndef ARGENTUM_MESSAGESERIALIZER_H
#define ARGENTUM_MESSAGESERIALIZER_H
#include "map"
#include "Serializer.h"
#include "../Socket.h"

class Message;

class MessageSerializer {
    std::vector<Serializer*> serializers;
    std::map<int,int> serializersTable;
public:
    MessageSerializer();
    std::string serialize(Message* message);
    Message* deserialize(int messageId,unsigned char * data,uint32_t len_data);
    ~MessageSerializer();
};


#endif //ARGENTUM_MESSAGESERIALIZER_H
