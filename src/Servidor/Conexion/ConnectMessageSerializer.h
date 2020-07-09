//
// Created by franco on 7/7/20.
//

#ifndef ARGENTUM_CONNECTMESSAGESERIALIZER_H
#define ARGENTUM_CONNECTMESSAGESERIALIZER_H


#include "Serializer.h"

class ConnectMessageSerializer: public Serializer {
public:
    char* serialize(Message *message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_CONNECTMESSAGESERIALIZER_H
