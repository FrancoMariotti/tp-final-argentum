#include "Mapa.h"
#include "PlayableCharacter.h"
#include "Npc.h"

Mapa::Mapa(int ancho,int alto):ancho(ancho),alto(alto) {}

void Mapa::addPlayableCharacter(PlayableCharacter* character) {
    this->characters.push_back(character);
}

void Mapa::addNpc(Npc* npc) {
    this->npcs.push_back(npc);
}

void Mapa::mover(Position& actual,Position& hasta) {
    //estaria bueno tener un solo iterador que recorra ambas listas.
    std::vector<PlayableCharacter*>::iterator itrCharacters;
    for (itrCharacters = characters.begin() ; itrCharacters != characters.end(); ++itrCharacters) {
        if((*itrCharacters)->colisiono(hasta)) return;
    }

    std::vector<Npc*>::iterator itrNpcs;
    for (itrNpcs = npcs.begin() ; itrNpcs != npcs.end(); ++itrNpcs) {
        if((*itrNpcs)->colisiono(hasta)) return;
    }
    actual = hasta;
}


GameObject* Mapa::findClosestCharacter(Position pos, int range) {
    //EL MAPA DEBERIA TEENR UN VECTOR CON TODOS LOS PERSONAJES JUGABLES,ESE VECTOR ES CHARATERS
    if (characters.empty()) return NULL;
    int minDist = (characters.front())->distanceTo(pos);
    PlayableCharacter* enemy = NULL;
    std::vector<PlayableCharacter*>::iterator it;
    for (it = characters.begin() ; it != characters.end(); ++it) {
        //HAY QUE CREAR EL METODO GET DISTANCE
        int currDist = (*it)->distanceTo(pos);
        if (currDist <= range && currDist <= minDist) {
            minDist = currDist;
            enemy = (*it);
        }
    }
    return enemy;
}

Mapa::~Mapa() = default;
