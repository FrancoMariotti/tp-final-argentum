#include "client_qt_loginmediator.h"
#include <QApplication>
#include <Common/Socket.h>

int QtApp(int argc, char*argv[], Socket& clientSocket);

int main(int argc, char *argv[]) {
    try{
        Socket clientSocket;
        //ProxySocket proxySocket;
        //std::thread proxyServer(server, std::ref(proxySocket));
        QtApp(argc, argv, clientSocket);
        std::cout << "saliendo QT" << std::endl;
        /*si se levanto la conexion lanzo SDL, caso contrario termina la ejecucion y no pasa nada
         * if(socket != -1){
         * Client client(socket)
         * client.run()*/
        //proxyServer.join();
    } catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}


int QtApp(int argc, char*argv[], Socket& clientSocket){
    QApplication a(argc, argv);
    LoginMediator loginMediator(clientSocket);
    loginMediator.show();
    return a.exec();
}