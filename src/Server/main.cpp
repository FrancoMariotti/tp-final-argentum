#include <Server/Connection/Server.h>

#define ERROR 1

int main(int argc, char const *argv[]) {

    //Verifico que se ingresen la cantidad de parametros correctos
    if (argc != 2) {
        std::cout << "Cantidad incorrecta de parametros" << std::endl;
        std::cout << "El parametro ingresado debe ser la ruta del archivo de configuracion" << std::endl;
        return ERROR;
    }

    try {
        FileParser parser(argv[1]);
        Json::Value info = parser.read("serverInfo");
        Server server(info["port"].asString(), argv[1],
                info["playersMapPath"].asString()
                ,info["playersInfoPath"].asString());
        server.start();
    } catch (std::exception &e) {
        printf("%s", e.what());
        return ERROR;
    } catch (...){
        printf("%s", "Unknow error");
        return ERROR;
    }

    return 0;
}