#ifndef ARGENTUM_LOGINMESSAGESERIALIZER_H
#define ARGENTUM_LOGINMESSAGESERIALIZER_H


#include "Serializer.h"

class LoginMessageSerializer:public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data, uint32_t len_data) override;
};


#endif //ARGENTUM_LOGINMESSAGESERIALIZER_H
