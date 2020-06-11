#ifndef ARGENTUM_MAPA_H
#define ARGENTUM_MAPA_H
#include "vector"
#include "Position.h"

class GameObject;
class Npc;
class PlayableCharacter;

class Mapa {
    int ancho;
    int alto;
    std::vector<Npc*> npcs;
    std::vector<PlayableCharacter*> characters;

    public:
        Mapa(int ancho,int alto);
        void addPlayableCharacter(PlayableCharacter* character);
        void addNpc(Npc* npc);
        void mover(Position& actual,Position& hasta);
        GameObject* findClosestCharacter(Position pos, int range);
        ~Mapa();
};

#endif //ARGENTUM_MAPA_H
