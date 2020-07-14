#include "client_qt_loginmediator.h"
#include "../../Proxy/src/common_proxy_socket.h"
#include "../../Proxy/src/common_message.h"
#include <thread>
#include <QApplication>

void server(ProxySocket& proxySocket);

int QtApp(int argc, char*argv[], ProxySocket& proxySocket);

int main(int argc, char *argv[]) {
    ProxySocket proxySocket;
    std::thread proxyServer(server, std::ref(proxySocket));

    QtApp(argc, argv, proxySocket);
    std::cout << "saliendo QT" << std::endl;

    proxyServer.join();
    return 0;
}


void server(ProxySocket& proxySocket){
    std::cout << "server running" << std::endl;
    int i = 0;
    while(i < 10){
        std::unique_ptr<Message> msg = proxySocket.readServer();
        std::cout << "ID_Server: " << msg->getId() << std::endl;
        if(msg->getId() == CONNECT_MESSAGE_ID){
            proxySocket.writeToClient(std::unique_ptr<Message>(new Accept(0)));
        }
        i++;
    }
    std::cout << "server shut" << std::endl;
}


int QtApp(int argc, char*argv[], ProxySocket& proxySocket){
    QApplication a(argc, argv);
    LoginMediator loginMediator(proxySocket);
    loginMediator.show();


    return a.exec();
}