#include <Servidor/Modelo/EventMove.h>
#include <Servidor/Modelo/NormalWeapon.h>
#include <Servidor/Modelo/Log.h>
#include <Servidor/Modelo/Game.h>

int main(int argc, char const *argv[]) {
    Log* log = Log::instancia();

    log->write("Inicio Main Argentum Servidor");

    Offset offset(0,1);
    Event* event = new EventMove(offset);
    NormalWeapon sword(2, 5, SHORT);
    Equippable shield(2, 5);

    Game game("config/config.json");

    game.createPlayer("franco", "human", "wizard");
    game.createPlayer("franco2", "human", "wizard");
    //game.createNpc("goblin");
    game.equipWeapon(&sword, "franco");
    game.equipProtection("franco2", shield, SHIELD);
    event->execute(game,"franco");
    game.attackPlayer("franco","franco2");
    game.attackPlayer("franco","franco2");
    game.attackPlayer("franco","franco2");

    delete event;

    log->close();
    return 0;
}
