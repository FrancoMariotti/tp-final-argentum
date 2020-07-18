#include "client_qt_loginmediator.h"
#include <QApplication>
#include <Common/Socket.h>
#include <Proxy/src/client_client.h>

int QtApp(int argc, char*argv[], Socket& socket, std::string& gui_username);

int main(int argc, char *argv[]) {
    try{
        Socket socket;
        std::string gui_username;
        /*si se levanto la conexion lanzo SDL,
         * caso contrario termina la ejecucion y no pasa nada*/
        QtApp(argc, argv, socket, gui_username);
        std::cout << "saliendo QT" << std::endl;
        Client client(socket);
        client.run(gui_username);
        client.stop();

    } catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}


int QtApp(int argc, char*argv[], Socket& socket, std::string& gui_username){
    QApplication a(argc, argv);
    LoginMediator loginMediator(socket, gui_username);
    loginMediator.show();
    return a.exec();
}