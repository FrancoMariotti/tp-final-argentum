//Using SDL, SDL_image, standard math, and strings
#include "client_client.h"

#include "server_proxy_server.h"

int main(int argc, char* args[]) {
    try {
        ProxySocket proxySocket;
        ProxyServer proxyServer(proxySocket);
        proxyServer.start();
        Client client(proxySocket);
        client.run();
        proxyServer.stop();
        client.stop();
        proxyServer.join();
    } catch (std::exception &e) {
        printf("%s", e.what());
        return 1;
    } catch (...){
        printf("%s", "Unknow error");
        return 1;
    }

    return 0;
}
