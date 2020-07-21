#include "client_qt_loginmediator.h"
#include <QApplication>
#include <Common/Socket.h>
#include <Client/src/client_client.h>

int QtApp(int argc, char*argv[], Socket& socket, std::string& gui_username,bool& finished);

int main(int argc, char *argv[]) {
    try{
        Socket socket;
        std::string gui_username;
        /*si se levanto la conexion lanzo SDL,
         * caso contrario termina la ejecucion y no pasa nada*/
        bool finished = false;
        QtApp(argc, argv, socket, gui_username,finished);
        std::cout << "saliendo QT" << std::endl;
        if(!finished) return 0;
        Client client(socket);
        client.run(gui_username);
        client.stop();

    } catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
    return 0;
}


int QtApp(int argc, char*argv[], Socket& socket, std::string& gui_username,bool& finished){
    QApplication a(argc, argv);
    LoginMediator loginMediator(socket, gui_username,finished);
    loginMediator.show();
    return a.exec();
}