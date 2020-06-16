#include <Servidor/Modelo/EventMove.h>
#include "Modelo/Game.h"

int main(int argc, char const *argv[]) {
    Offset offset(0,1);
    Event* event = new EventMove(offset);

    Game game("config/mapa.json");
    game.createPlayer("franco");
    event->execute(game,"franco");
    delete event;
    //Mobility* mobility= new NonMovable();
    //Npc npc(100, mobility, 0, 1, map);
    //PlayableCharacter character (100, 4, 5, map);

    //for (int i = 0; i < 10; i++) {
    //   npc.move();
    //}
    //npc.printPosition();

    //Offset offset(1, 0);
    //character.move(offset);
    //character.printPosition();
    //character.move(offset);
    //character.printPosition();
    return 0;
}
