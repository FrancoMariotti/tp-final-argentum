#ifndef ARGENTUM_CONNECTMESSAGESERIALIZER_H
#define ARGENTUM_CONNECTMESSAGESERIALIZER_H


#include "Serializer.h"

class ConnectMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data,uint32_t len_data) override;
};


#endif //ARGENTUM_CONNECTMESSAGESERIALIZER_H
