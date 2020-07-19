#ifndef ARGENTUM_SPAWNSTATICOBJECTSMESSAGESERIALIZER_H
#define ARGENTUM_SPAWNSTATICOBJECTSMESSAGESERIALIZER_H
#include "Serializer.h"

class SpawnStaticObjectsMessageSerializer: public Serializer {
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data,uint32_t len_data) override;
};

#endif //ARGENTUM_SPAWNSTATICOBJECTSMESSAGESERIALIZER_H
