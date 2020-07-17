#include "client_qt_loginmediator.h"
#include "../../Proxy/src/common_proxy_socket.h"
#include "../../Proxy/src/common_message.h"
#include <thread>
#include <QApplication>
#include <Proxy/src/common_socket.h>

void server(ProxySocket& proxySocket);

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


void server(ProxySocket& proxySocket){
    try{
        std::cout << "server running" << std::endl;
        int i = 0;
        while(i < 10){
            std::unique_ptr<Message> msg = proxySocket.readServer();
            std::cout << "ID_Server: " << msg->getId() << std::endl;
            int id = msg->getId();
            if (id == PROXY_CONNECT_MESSAGE_ID){
                t_login login =  msg->getLogin();
                proxySocket.writeToClient(std::unique_ptr<Message>
                (new Accept(login.username == "host"
                && login.password == "service")));
            
            } else if (id == LOGIN_MESSAGE_ID){
                t_login login = msg->getLogin();
                proxySocket.writeToClient(std::unique_ptr<Message>
                (new Accept(login.username == "username"
                && login.password == "password")));
            
            } else if (id == SIGNUP_MESSAGE_ID){
                t_login login = msg->getLogin();
                proxySocket.writeToClient(std::unique_ptr<Message> 
                        (new Accept(login.username == "username"
                        && login.password == "password")));
            
            } else if (id == CREATE_MESSAGE_ID){
                t_create_connect create =  msg->getConnectData();
                std::cout << "Server: " <<  create.username << " " << create.password << std::endl;
                proxySocket.writeToClient(std::unique_ptr<Message>
                        (new Accept(create.username == "username"
                        && create.password == "password")));
            } 
            i++;
        }
        std::cout << "server shut" << std::endl;
    } catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
}


int QtApp(int argc, char*argv[], Socket& clientSocket){
    QApplication a(argc, argv);
    LoginMediator loginMediator(clientSocket);
    loginMediator.show();
    return a.exec();
}