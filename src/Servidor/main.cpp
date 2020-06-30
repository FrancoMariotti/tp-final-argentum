#include <Servidor/Modelo/EventMove.h>
#include <Servidor/Modelo/Log.h>
#include <Servidor/Modelo/Game.h>
#include <Servidor/Modelo/RangeWeapon.h>
#include <Servidor/Modelo/LifePotion.h>

int main(int argc, char const *argv[]) {
    Log* log = Log::instancia();

    log->write("Inicio Main Argentum Servidor");

    Offset offset(0,1);
    Event* event = new EventMove(offset);
    NormalWeapon sword("sword", 2, 5);
    Protection shield("shield", 2, 5, SHIELD);
    LifePotion lifePotion("megaLifePotion",1000);

    Game game("config/config.json");

    game.createPlayer("franco", "human", "wizard");
    game.createPlayer("franco2", "human", "wizard");
    game.storeInInventory("franco", &sword);
    game.equip("franco", 0);
    game.storeInInventory("franco2", &shield);
    game.equip("franco2", 0);
    event->execute(game,"franco");
    game.attackPlayer("franco","franco2");
    game.attackPlayer("franco","franco2");
    game.attackPlayer("franco","franco2");
    game.storeInInventory("franco2", &lifePotion);
    game.equip("franco2", 1);
    game.unequip("franco2", 0);
    delete event;

    log->close();
    return 0;
}
