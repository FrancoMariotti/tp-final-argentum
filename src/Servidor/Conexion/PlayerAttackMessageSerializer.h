//
// Created by franco on 7/7/20.
//

#ifndef ARGENTUM_PLAYERATTACKMESSAGESERIALIZER_H
#define ARGENTUM_PLAYERATTACKMESSAGESERIALIZER_H


#include <Proxy/src/common_message.h>
#include "Serializer.h"

class PlayerAttackMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_PLAYERATTACKMESSAGESERIALIZER_H
