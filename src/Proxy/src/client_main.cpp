//Using SDL, SDL_image, standard math, and strings
#include "client_client.h"

#include "server_proxy_server.h"

int main(int argc, char* args[]) {
    try {
        std::string hostname = args[1];
        std::string service = args[2];
        Client client(hostname,service);
        client.run();
        client.stop();
    } catch (std::exception &e) {
        printf("%s", e.what());
        return 1;
    } catch (...){
        printf("%s", "Unknow error");
        return 1;
    }

    return 0;
}
