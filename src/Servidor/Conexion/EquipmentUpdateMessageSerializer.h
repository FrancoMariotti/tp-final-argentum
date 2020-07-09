//
// Created by franco on 7/7/20.
//

#ifndef ARGENTUM_EQUIPMENTUPDATEMESSAGESERIALIZER_H
#define ARGENTUM_EQUIPMENTUPDATEMESSAGESERIALIZER_H


#include "Serializer.h"

class EquipmentUpdateMessageSerializer: public Serializer {
public:
    char* serialize(Message *message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_EQUIPMENTUPDATEMESSAGESERIALIZER_H
