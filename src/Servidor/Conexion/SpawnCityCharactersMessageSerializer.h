//
// Created by franco on 7/7/20.
//

#ifndef ARGENTUM_SPAWNCITYCHARACTERSMESSAGESERIALIZER_H
#define ARGENTUM_SPAWNCITYCHARACTERSMESSAGESERIALIZER_H


#include "Serializer.h"

class SpawnCityCharactersMessageSerializer: public Serializer {
public:
    char* serialize(Message *message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_SPAWNCITYCHARACTERSMESSAGESERIALIZER_H
