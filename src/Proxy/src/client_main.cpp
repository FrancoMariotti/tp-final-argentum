//Using SDL, SDL_image, standard math, and strings
#include "client_client.h"

//test
#include "client_protected_list.h"
#include "common_message.h"

//Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void test();

int main(int argc, char* args[]) {
    try {
        //test();
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

void test(){
    ProtectedList<std::unique_ptr<Message>> serverEvents;
    serverEvents.push(std::unique_ptr<Message>(new UseItem(1)));
    serverEvents.push(std::unique_ptr<Message>(new UseItem(2)));
    serverEvents.push(std::unique_ptr<Message>(new UseItem(3)));

    std::list<std::unique_ptr<Message>> events = serverEvents.consume();
    std::cout << "Lista a iterar" << std::endl;
    for(auto & msg : events){
        std::cout << msg->getId() << msg->getIndex() << std::endl;
    }
    std::cout << "server events" << std::endl;
    serverEvents.testShow();

    std::cout << "client events" << std::endl;
    BlockingQueue<std::unique_ptr<Message>> clientEvents;
    clientEvents.push(std::unique_ptr<Message>(new UseItem(1)));
    clientEvents.push(std::unique_ptr<Message>(new UseItem(2)));

    std::cout << clientEvents.pop()->getIndex() << std::endl;
    std::cout << clientEvents.pop()->getIndex() << std::endl;
    clientEvents.testShow();
}