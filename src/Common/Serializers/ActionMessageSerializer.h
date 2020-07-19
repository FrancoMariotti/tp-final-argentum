#ifndef ARGENTUM_ACTIONMESSAGESERIALIZER_H
#define ARGENTUM_ACTIONMESSAGESERIALIZER_H

#include "Serializer.h"

class ActionMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(unsigned char *data, uint32_t len_data) override;
};


#endif //ARGENTUM_ACTIONMESSAGESERIALIZER_H
