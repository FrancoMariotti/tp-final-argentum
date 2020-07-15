//
// Created by agustin on 15/7/20.
//

#include "QtServer.h"

int main(int argc, char const *argv[]) {
    try{
        QtServer qtServer(argv[1]);
        qtServer();
    } catch(std::exception &e){
        printf("%s", e.what());
        return 1;
    } catch(...){
        printf("Unknow error!");
        return 1;
    }
    return 0;
}
