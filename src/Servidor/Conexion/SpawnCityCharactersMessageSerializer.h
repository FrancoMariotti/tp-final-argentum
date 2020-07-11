//
// Created by franco on 10/7/20.
//

#ifndef ARGENTUM_SPAWNCITYCHARACTERSMESSAGESERIALIZER_H
#define ARGENTUM_SPAWNCITYCHARACTERSMESSAGESERIALIZER_H


#include "Serializer.h"

class SpawnCityCharactersMessageSerializer: public Serializer {
    std::string serialize(Message *message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_SPAWNCITYCHARACTERSMESSAGESERIALIZER_H
