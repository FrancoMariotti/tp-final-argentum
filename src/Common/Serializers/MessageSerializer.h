#ifndef ARGENTUM_MESSAGESERIALIZER_H
#define ARGENTUM_MESSAGESERIALIZER_H
#include "map"
#include "Serializer.h"
#include "../Socket.h"

class Message;

class MessageSerializer {
    std::vector<Serializer*> serializers;
    std::map<int,int> serializersTable;
public:
    MessageSerializer();
    //Busca el serializador correspondiente para el mensaje recibido y lo serializa.
    //Lanza OSError en caso de no encontrar un serializador para el mismo.
    std::string serialize(Message* message);
    //Busca el serializador correspondiente para el mensaje recibido y lo des serializa.
    //En caso de no encontrar un serializador devuelve nullptr
    Message* deserialize(int messageId,unsigned char * data,uint32_t len_data);
    ~MessageSerializer();
};


#endif //ARGENTUM_MESSAGESERIALIZER_H
