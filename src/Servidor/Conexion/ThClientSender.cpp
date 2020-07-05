#include "ThClientSender.h"

ThClientSender::ThClientSender(Socket client,BlockingQueue<Message*>& messages):client(std::move(client)),messages(messages) {
    this->keepTalking = true;
}

void ThClientSender::start() {
    Thread::start();
}

void ThClientSender::run() {
    Message *message;
    while(keepTalking) {
        message = messages.pop();
        try {
            //si falla el send se lanza una excepcion

            client.send(message->serialize());
        } catch(std::exception &e) {
            printf("%s", e.what());
            stop();
        }


        //logica de protocolo
        /*const char* data = first.serialize();
        u_int16_t len_data = strlen(data);
        send(cliente,len_data);
        cliente.send(data,len_data);*/
    }

}

void ThClientSender::stop() {
    keepTalking = false;
    client.shutdown(SHUT_WR);
}
