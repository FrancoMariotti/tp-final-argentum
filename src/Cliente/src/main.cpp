#include "client_qt_loginmediator.h"
//#include "../../Proxy/src/common_proxy_socket.h"
//#include "../../Proxy/src/common_message.h"
#include <thread>
#include <QApplication>

//void server(ProxySocket& proxySocket);

int QtApp(int argc, char*argv[]);

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    LoginMediator loginMediator;
    loginMediator.show();


    //ProxySocket proxySocket;
    //std::thread proxyServer(server, proxySocket);
  //  QtApp(argc, argv);
    return a.exec();

//    return 0;
}

/*
void server(ProxySocket& proxySocket){
    std::cout << "server running" << std::endl;
    int i = 0;
    while(i < 10){
        std::unique_ptr<Message> msg = proxySocket.readServer();
        std::cout << msg->getId() << std::endl;
        i++;
    }
}
*/

int QtApp(int argc, char*argv[]){
    return 0;
 }