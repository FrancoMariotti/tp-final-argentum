#include <Servidor/Modelo/EventMove.h>
#include <Servidor/Modelo/Log.h>
#include <Servidor/Modelo/Game.h>
#include <Servidor/Modelo/RangeWeapon.h>
#include <Servidor/Modelo/LifePotion.h>

int main(int argc, char const *argv[]) {

    NormalWeapon sword("sword", 2, 5, 0);
    Protection helmet("helmet", 3, 6, HELMET, 0);
    Protection shield("shield", 2, 5, SHIELD, 0);
    Protection armour("armour", 4, 7, ARMOUR, 0);
    LifePotion lifePotion("megaLifePotion",1000, 0);

    Game game("config/config.json");

    return 0;
}
