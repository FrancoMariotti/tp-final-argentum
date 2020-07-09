//
// Created by franco on 7/7/20.
//

#ifndef ARGENTUM_COMMANDMESSAGESERIALIZER_H
#define ARGENTUM_COMMANDMESSAGESERIALIZER_H


#include "Serializer.h"

class CommandMessageSerializer: public Serializer {
public:
    char* serialize(Message *message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_COMMANDMESSAGESERIALIZER_H
