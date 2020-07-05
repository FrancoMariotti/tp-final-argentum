#ifndef ARGENTUM_MOVEMENTMESSAGESERIALIZER_H
#define ARGENTUM_MOVEMENTMESSAGESERIALIZER_H


#include "Serializer.h"

class MovementMessageSerializer: public Serializer {
public:
    std::string serialize(Message* messages) override;
    Message* deserialize(char * data) override;
};


#endif //ARGENTUM_MOVEMENTMESSAGESERIALIZER_H
