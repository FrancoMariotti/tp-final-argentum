//
// Created by franco on 7/7/20.
//

#ifndef ARGENTUM_USEITEMMESSAGESERIALIZER_H
#define ARGENTUM_USEITEMMESSAGESERIALIZER_H


#include "Serializer.h"

class UseItemMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_USEITEMMESSAGESERIALIZER_H
