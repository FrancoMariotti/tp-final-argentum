#include <Client/Qt/include/client_qt_loginmediator.h>
//#include <QApplication>
#include "client_client.h"

int QtApp(int argc, char*args[], Socket& socket);

int main(int argc, char* args[]) {
    try {
        Socket socket;
        QtApp(argc, args, socket);
        //std::string hostname = args[1];
        //std::string service = args[2];
        /*Si el cliente decide no conectarse, se debe terminar la ejecucion sin correr SDL*/
        //if(socket != -1){
            Client client(socket);
        client.run("NaN");
            client.stop();
        //}
    } catch (std::exception &e) {
        printf("%s", e.what());
        return 1;
    } catch (...){
        printf("%s", "Unknow error");
        return 1;
    }

    return 0;
}

int QtApp(int argc, char* args[], Socket& socket){
   // QApplication a(argc, args);
   std::string dummy;
    //LoginMediator loginMediator(socket, dummy);
    //loginMediator.show();
    return 0; //a.exec();
}