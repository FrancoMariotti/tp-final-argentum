//
// Created by franco on 15/7/20.
//

#ifndef ARGENTUM_INVENTORYMESSAGESERIALIZER_H
#define ARGENTUM_INVENTORYMESSAGESERIALIZER_H


#include "Serializer.h"

class InventoryMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data, uint32_t len_data) override;
};


#endif //ARGENTUM_INVENTORYMESSAGESERIALIZER_H
