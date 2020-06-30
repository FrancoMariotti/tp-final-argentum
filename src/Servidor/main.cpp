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
    NormalWeapon sword("sword", 2, 5, 0);
    Protection helmet("helmet", 3, 6, HELMET, 0);
    Protection shield("shield", 2, 5, SHIELD, 0);
    Protection armour("armour", 4, 7, ARMOUR, 0);
    LifePotion lifePotion("megaLifePotion",1000, 0);

    Game game("config/config.json");

    game.createPlayer("franco", "human", "wizard");
    game.createPlayer("franco2", "human", "wizard");
    game.storeInInventory("franco", &sword);
    game.equip("franco", 0);
    game.storeInInventory("franco2", &shield);
    game.equip("franco2", 0);
    game.storeInInventory("franco2", &helmet);
    game.equip("franco2", 1);
    game.storeInInventory("franco2", &armour);
    game.equip("franco2", 2);
    game.unequip("franco2", 1);
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
