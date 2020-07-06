#include <Servidor/Conexion/Server.h>

int main(int argc, char const *argv[]) {
    Server server("8081");
    server.start();

    return 0;
}
