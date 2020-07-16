//
// Created by franco on 16/7/20.
//

#ifndef ARGENTUM_EQUIPMENTMESSAGESERIALIZER_H
#define ARGENTUM_EQUIPMENTMESSAGESERIALIZER_H


#include "Serializer.h"

class EquipmentMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data, uint32_t len_data) override;
};


#endif //ARGENTUM_EQUIPMENTMESSAGESERIALIZER_H
