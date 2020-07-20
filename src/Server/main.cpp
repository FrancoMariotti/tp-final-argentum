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
        /*Server server("8081","config/config.json",
                "PersistenceFiles/playersInfoMapFile.bin",
                "PersistenceFiles/playersInfoFile.bin");*/
        FileParser parser(argv[1]);
        std::string port = parser.read("port").asString();
        Server server(port, argv[1],
                "PersistenceFiles/playersInfoMapFile.bin",
                "PersistenceFiles/playersInfoFile.bin");
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