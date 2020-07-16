#ifndef ARGENTUM_CONSOLEOUTPUTMESSAGESERIALIZER_H
#define ARGENTUM_CONSOLEOUTPUTMESSAGESERIALIZER_H


#include "Serializer.h"

class ConsoleOutputMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data, uint32_t len_data) override;
};


#endif //ARGENTUM_CONSOLEOUTPUTMESSAGESERIALIZER_H
