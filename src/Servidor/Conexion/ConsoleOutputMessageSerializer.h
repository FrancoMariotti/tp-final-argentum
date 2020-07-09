//
// Created by franco on 7/7/20.
//

#ifndef ARGENTUM_CONSOLEOUTPUTMESSAGESERIALIZER_H
#define ARGENTUM_CONSOLEOUTPUTMESSAGESERIALIZER_H


#include "Serializer.h"

class ConsoleOutputMessageSerializer: public Serializer {
public:
    char* serialize(Message *message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_CONSOLEOUTPUTMESSAGESERIALIZER_H
