#ifndef ARGENTUM_CLIENTCONNECTION_H
#define ARGENTUM_CLIENTCONNECTION_H


#include <Common/Messages/Message.h>
#include <memory>
#include <Common/Socket.h>
#include "ThClientSender.h"
#include "ThClientReceiver.h"

class ClientConnection {
    int id;
    Socket client;
    ThClientSender sender;
    BlockingQueue<event_t> events;
    ThClientReceiver receiver;
    bool dead;
    void stop();
    friend class ThClientReceiver;
public:
    ClientConnection(int id,Socket client,ProtectedList<std::unique_ptr<Message>>& messages);
    ClientConnection(ClientConnection&) = delete;
    bool isDead() const;
    int getId();
    void joinResources();
    //encola en la lista de mensajes del thread sender el
    //mensaje con id param:messageId y la data param:data del mensaje
    void sendMessage(int messageId,std::string data);
    //envia por el socket la respuesta answer recibida por parametro.
    void sendLoginReponse(int answer);
    void start();
    void finish();
    ~ClientConnection();
};


#endif //ARGENTUM_CLIENTCONNECTION_H
