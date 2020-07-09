#ifndef ARGENTUM_STATSUPDATEMESSAGESERIALIZER_H
#define ARGENTUM_STATSUPDATEMESSAGESERIALIZER_H


#include "Serializer.h"

class StatsUpdateMessageSerializer: public Serializer {
public:
    std::string serialize(Message *message) override;
    Message * deserialize(char *data) override;
};


#endif //ARGENTUM_STATSUPDATEMESSAGESERIALIZER_H
