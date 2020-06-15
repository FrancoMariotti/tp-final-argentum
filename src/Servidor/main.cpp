#include "Modelo/Mobility.h"
#include "Modelo/Npc.h"
#include "Modelo/PlayableCharacter.h"
#include "Modelo/Map.h"
#include "Modelo/Factory.h"

int main(int argc, char const *argv[]) {

    MapFactory factory("config/mapa.json");
    Map map = factory.create();
    Mobility* mobility= new NonMovable();
    Npc npc(100, mobility, 0, 1, map);
    PlayableCharacter character (100, 4, 5, map);

    for (int i = 0; i < 10; i++) {
       npc.move();
    }
    npc.printPosition();

    //Offset offset(1, 0);
    //character.move(offset);
    //character.printPosition();
    //character.move(offset);
    //character.printPosition();
    return 0;
}
