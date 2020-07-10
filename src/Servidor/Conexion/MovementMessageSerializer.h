#ifndef ARGENTUM_MOVEMENTMESSAGESERIALIZER_H
#define ARGENTUM_MOVEMENTMESSAGESERIALIZER_H


#include <Proxy/src/common_socket.h>
#include "Serializer.h"

class MovementMessageSerializer: public Serializer {
public:
    void serialize(Socket& socket,Message* messages) override;
    Message* deserialize(char * data) override;
};


#endif //ARGENTUM_MOVEMENTMESSAGESERIALIZER_H
