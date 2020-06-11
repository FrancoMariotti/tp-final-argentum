#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <Servidor/Modelo/Movilidad.h>
#include <Servidor/Modelo/Npc.h>
#include <Servidor/Modelo/PlayableCharacter.h>
#include "Modelo/Mapa.h"
#include "Modelo/Factory.h"

int main(int argc, char const *argv[]) {

    MapaFactory factory("config/mapa.json");
    Mapa mapa = factory.create();
    Movilidad* movilidad= new Movible();
    Npc npc(100, movilidad, 0, 0, mapa);
    PlayableCharacter character (100, movilidad, -4, -3, mapa);
    for (int i = 0; i < 10; i++) {
       npc.move();
       npc.printPosition();
    }

    return 0;
}
