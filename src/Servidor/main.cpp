#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "Modelo/Mapa.h"
#include "Modelo/Factory.h"

int main(int argc, char const *argv[]) {

    MapaFactory factory("config/mapa.json");
    Mapa mapa = factory.create();

    return 0;
}
