#include "Mapa.h"

Mapa::Mapa(int ancho,int alto):ancho(ancho),alto(alto) {}

void Mapa::agregar(GameObject* objeto) {
    objetos.push_back(objeto);
}

void Mapa::mover(Posicion& actual,Posicion& hasta) {
    std::vector<GameObject*>::iterator it;
    for (it = objetos.begin() ; it != objetos.end(); ++it) {
        if((*it)->colisiono(hasta)) return;
    }
    actual = hasta;
}

Personaje* Mapa::findClosestCharacter(Posicion pos, int range) {
    //EL MAPA DEBERIA TEENR UN VECTOR CON TODOS LOS PERSONAJES JUGABLES,ESE VECTOR ES CHARATERS
    int minDist = characters.front()->getDistance(pos);
    Personaje* enemy = NULL;
    std::vector<Personaje*>::iterator it;
    for (it = characters.begin() ; it != characters.end(); ++it) {
        //HAY QUE CREAR EL METODO GET DISTANCE
        int currDist = (*it)->getDistance(pos);
        if (currDist <= range && currDist < minDist) {
            minDist = currDist;
            enemy = (*it);
        }
    }
    return enemy;

}

Mapa::~Mapa() {}
