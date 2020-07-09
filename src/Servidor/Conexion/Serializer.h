#ifndef ARGENTUM_SERIALIZER_H
#define ARGENTUM_SERIALIZER_H

#include <Proxy/src/common_message.h>

class Serializer {
public:
    virtual char* serialize(Message* message) = 0;
    virtual Message* deserialize(char * data) = 0;
    virtual ~Serializer() = default;
};

#endif //ARGENTUM_SERIALIZER_H
