//
// Created by franco on 7/7/20.
//

#ifndef ARGENTUM_INVENTORYUPDATEMESSAGESERIALIZER_H
#define ARGENTUM_INVENTORYUPDATEMESSAGESERIALIZER_H


#include "Serializer.h"

class InventoryUpdateMessageSerializer: public Serializer {
public:
    char* serialize(Message *message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_INVENTORYUPDATEMESSAGESERIALIZER_H
