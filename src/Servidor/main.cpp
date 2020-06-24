#include <Servidor/Modelo/EventMove.h>
#include <Servidor/Modelo/NormalWeapon.h>
#include <fstream>
#include <Servidor/Modelo/Log.h>

#include "Modelo/Game.h"
int main(int argc, char const *argv[]) {
    Log* log = Log::instancia();

    log->write("Inicio Main Argentum Servidor");

    Offset offset(0,1);
    Event* event = new EventMove(offset);
    NormalWeapon sword(2, 5, SHORT);
    Equippable shield(2, 5);

    Game game("config/config.json");
    /*
    MI IDEA SERIA TENER UN METODO EN GAME QUE CREE TODOS LOS NPCS QUE DEBERIQ HABER EN EL MAPA
    game.createNpcs();
    */
    game.createPlayer("franco", "human", "wizard");
    game.createPlayer("franco2", "human", "wizard");
    //game.createNpc("goblin");
    game.equipWeapon(&sword, "franco");
    game.equipProtection("franco2", shield, 1);
    event->execute(game,"franco");
    game.attackPlayer("franco","franco2");
    game.attackPlayer("franco","franco2");
    game.attackPlayer("franco","franco2");

    delete event;

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
    log->cerrar();
    return 0;
}
