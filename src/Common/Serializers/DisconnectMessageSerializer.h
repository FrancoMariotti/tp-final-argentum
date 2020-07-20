//
// Created by franco on 20/7/20.
//

#ifndef ARGENTUM_DISCONNECTMESSAGESERIALIZER_H
#define ARGENTUM_DISCONNECTMESSAGESERIALIZER_H


#include "Serializer.h"

class DisconnectMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data, uint32_t len_data) override;
};


#endif //ARGENTUM_DISCONNECTMESSAGESERIALIZER_H
