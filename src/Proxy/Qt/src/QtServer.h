//
// Created by agustin on 15/7/20.
//

#ifndef ARGENTUM_QTSERVER_H
#define ARGENTUM_QTSERVER_H


#include <Proxy/src/common_socket.h>

class QtServer {
private:
    Socket acep_socket;
    bool keep_talking;
public:
    explicit QtServer(const char* service);
    
    void operator()();

    void start();
};


#endif //ARGENTUM_QTSERVER_H
