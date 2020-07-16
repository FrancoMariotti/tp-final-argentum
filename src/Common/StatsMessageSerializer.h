//
// Created by franco on 15/7/20.
//

#ifndef ARGENTUM_STATSMESSAGESERIALIZER_H
#define ARGENTUM_STATSMESSAGESERIALIZER_H


#include "Serializer.h"

class StatsMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data, uint32_t len_data) override;
};


#endif //ARGENTUM_STATSMESSAGESERIALIZER_H
