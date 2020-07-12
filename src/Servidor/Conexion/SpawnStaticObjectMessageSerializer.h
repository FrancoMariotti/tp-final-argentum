//
// Created by franco on 10/7/20.
//

#ifndef ARGENTUM_SPAWNSTATICOBJECTMESSAGESERIALIZER_H
#define ARGENTUM_SPAWNSTATICOBJECTMESSAGESERIALIZER_H


#include "Serializer.h"

class SpawnStaticObjectMessageSerializer: public Serializer {
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data,uint16_t len_data) override;
};


#endif //ARGENTUM_SPAWNSTATICOBJECTMESSAGESERIALIZER_H
