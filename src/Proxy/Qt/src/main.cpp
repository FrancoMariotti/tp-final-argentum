#include "client_qt_loginmediator.h"
#include <QApplication>
#include <Common/Socket.h>
#include <Proxy/src/client_client.h>

int QtApp(int argc, char*argv[], Socket& socket);

int main(int argc, char *argv[]) {
    try{
        Socket socket;
        /*si se levanto la conexion lanzo SDL,
         * caso contrario termina la ejecucion y no pasa nada*/
        QtApp(argc, argv, socket);
        std::cout << "saliendo QT" << std::endl;
        Client client(socket);
        client.run();
        client.stop();

    } catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}


int QtApp(int argc, char*argv[], Socket& socket){
    QApplication a(argc, argv);
    LoginMediator loginMediator(socket);
    loginMediator.show();
    return a.exec();
}