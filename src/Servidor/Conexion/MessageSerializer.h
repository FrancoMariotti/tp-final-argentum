#ifndef ARGENTUM_MESSAGESERIALIZER_H
#define ARGENTUM_MESSAGESERIALIZER_H

#include <Proxy/src/common_message.h>
#include "map"
#include "Serializer.h"

class MessageSerializer {
    std::map<int,Serializer*> serializers;
public:
    MessageSerializer();
    std::string serialize(Message* message);
    Message* deserialize(int messageId,char * data);
    ~MessageSerializer();
};


#endif //ARGENTUM_MESSAGESERIALIZER_H
