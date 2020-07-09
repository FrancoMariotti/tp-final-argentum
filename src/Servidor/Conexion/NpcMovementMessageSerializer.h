//
// Created by franco on 7/7/20.
//

#ifndef ARGENTUM_NPCMOVEMENTMESSAGESERIALIZER_H
#define ARGENTUM_NPCMOVEMENTMESSAGESERIALIZER_H


#include "Serializer.h"

class NpcMovementMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_NPCMOVEMENTMESSAGESERIALIZER_H
