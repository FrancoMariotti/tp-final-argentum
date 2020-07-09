//
// Created by franco on 7/7/20.
//

#ifndef ARGENTUM_SPAWNNPCMESSAGESERIALIZER_H
#define ARGENTUM_SPAWNNPCMESSAGESERIALIZER_H


#include "Serializer.h"

class SpawnNpcMessageSerializer: public Serializer {
public:
    char* serialize(Message *message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_SPAWNNPCMESSAGESERIALIZER_H
