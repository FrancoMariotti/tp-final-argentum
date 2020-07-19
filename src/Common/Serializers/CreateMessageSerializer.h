//
// Created by franco on 7/7/20.
//

#ifndef ARGENTUM_CREATEMESSAGESERIALIZER_H
#define ARGENTUM_CREATEMESSAGESERIALIZER_H


#include "Serializer.h"

class CreateMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data,uint32_t len_data) override;
};


#endif //ARGENTUM_CREATEMESSAGESERIALIZER_H
