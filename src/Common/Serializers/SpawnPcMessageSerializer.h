//
// Created by franco on 12/7/20.
//

#ifndef ARGENTUM_SPAWNPCMESSAGESERIALIZER_H
#define ARGENTUM_SPAWNPCMESSAGESERIALIZER_H

#include "Serializer.h"

class SpawnPcMessageSerializer: public Serializer {
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data, uint32_t len_data) override;
};


#endif //ARGENTUM_SPAWNPCMESSAGESERIALIZER_H
