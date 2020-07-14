#ifndef ARGENTUM_MOVEMENTMESSAGESERIALIZER_H
#define ARGENTUM_MOVEMENTMESSAGESERIALIZER_H


#include <Common/Socket.h>
#include "Serializer.h"

class MovementMessageSerializer: public Serializer {
public:
    std::string serialize(Message* messages) override;
    Message* deserialize(unsigned char * data,uint16_t len_data) override;
};


#endif //ARGENTUM_MOVEMENTMESSAGESERIALIZER_H
