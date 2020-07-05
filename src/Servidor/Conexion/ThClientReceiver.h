#ifndef ARGENTUM_THCLIENTRECEIVER_H
#define ARGENTUM_THCLIENTRECEIVER_H


#include <Proxy/src/common_thread.h>
#include <Proxy/src/common_socket.h>
#include <Proxy/src/common_message.h>
#include <Proxy/src/common_blocking_queue.h>

class ThClientReceiver: public Thread {
public:
    ThClientReceiver(Socket client,BlockingQueue<Message>& messages);
    void start() override ;
    void run() override ;
    void stop();

};


#endif //ARGENTUM_THCLIENTRECEIVER_H
