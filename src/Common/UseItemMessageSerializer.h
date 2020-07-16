//
// Created by franco on 16/7/20.
//

#ifndef ARGENTUM_USEITEMMESSAGESERIALIZER_H
#define ARGENTUM_USEITEMMESSAGESERIALIZER_H


#include "Serializer.h"

class UseItemMessageSerializer: public Serializer {
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data, uint32_t len_data) override;
};


#endif //ARGENTUM_USEITEMMESSAGESERIALIZER_H
