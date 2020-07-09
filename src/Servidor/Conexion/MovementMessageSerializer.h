#ifndef ARGENTUM_MOVEMENTMESSAGESERIALIZER_H
#define ARGENTUM_MOVEMENTMESSAGESERIALIZER_H


#include "Serializer.h"

class MovementMessageSerializer: public Serializer {
public:
    char* serialize(Message* messages) override;
    Message* deserialize(char * data) override;
};


#endif //ARGENTUM_MOVEMENTMESSAGESERIALIZER_H
