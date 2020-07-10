//
// Created by franco on 7/7/20.
//

#ifndef ARGENTUM_DRAWMESSAGESERIALIZER_H
#define ARGENTUM_DRAWMESSAGESERIALIZER_H


#include "Serializer.h"

class DrawMessageSerializer: public Serializer {
public:
    void serialize(Socket& socket, Message* message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_DRAWMESSAGESERIALIZER_H
