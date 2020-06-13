//Using SDL, SDL_image, standard math, and strings
#include "client_client.h"

//Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480



int main(int argc, char* args[]) {
    try {
        Client client;
        client.run();
    } catch (std::exception &e) {
        printf("%s", e.what());
        return 1;
    } catch (...){
    printf("%s", "Unknow error");
        return 1;
    }

    return 0;
}
