//
// Created by franco on 15/7/20.
//

#ifndef ARGENTUM_COMMANDMESSAGESERIALIZER_H
#define ARGENTUM_COMMANDMESSAGESERIALIZER_H

#include "Serializer.h"

class CommandMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data, uint32_t len_data) override;
};


#endif //ARGENTUM_COMMANDMESSAGESERIALIZER_H
