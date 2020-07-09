#include <Servidor/Conexion/Server.h>

int main(int argc, char const *argv[]) {

    //if (argc != 2) return 1;

    try {
        //puerto hay que cargarlo de un archivo de configuracion
        //que es el mismo que me pasan por parametro
        Server server("8080","config/config.json");
        server.start();
    } catch (std::exception &e) {
        printf("%s", e.what());
        return 1;
    } catch (...){
        printf("%s", "Unknow error");
        return 1;
    }

    return 0;
}
