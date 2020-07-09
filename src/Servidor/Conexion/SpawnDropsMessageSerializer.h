//
// Created by franco on 7/7/20.
//

#ifndef ARGENTUM_SPAWNDROPSMESSAGESERIALIZER_H
#define ARGENTUM_SPAWNDROPSMESSAGESERIALIZER_H


#include "Serializer.h"

class SpawnDropsMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_SPAWNDROPSMESSAGESERIALIZER_H
