#include "Modelo/Mobility.h"
#include "Modelo/Npc.h"
#include "Modelo/PlayableCharacter.h"
#include "Modelo/Map.h"
#include "Modelo/Factory.h"

int main(int argc, char const *argv[]) {

    MapFactory factory("config/mapa.json");
    Map map = factory.create();
    Mobility* mobility= new Movable();
    Npc npc(100, mobility, 0, 0, map);
    PlayableCharacter character (100, mobility, 1, 1, map);
    /*
    for (int i = 0; i < 10; i++) {
       npc.move();
       npc.printPosition();
    }
    */
    Obstacle obstacle(1, 3, 2, 2);
    map.addObstacle(&obstacle);
    Offset offset(0, 1);
    character.move(offset);
    character.printPosition();
    character.move(offset);
    character.printPosition();
    return 0;
}
