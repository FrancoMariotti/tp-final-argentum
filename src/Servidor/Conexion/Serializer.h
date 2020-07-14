#ifndef ARGENTUM_SERIALIZER_H
#define ARGENTUM_SERIALIZER_H

#include <Common/Message.h>
#include <Common/Socket.h>


class Serializer {
public:
    virtual std::string serialize(Message* message) = 0;
    virtual Message* deserialize(unsigned char * data,uint16_t len_data) = 0;
    virtual ~Serializer() = default;
};

#endif //ARGENTUM_SERIALIZER_H
