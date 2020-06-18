#include <jsoncpp/json/json.h>
#include <iostream>
#include "Game.h"
#include "Factory.h"
#include "PlayableCharacter.h"
#include "Npc.h"

FileParser::FileParser(const std::string& filename):file(filename){}

Json::Value FileParser::read(const std::string& parameter) {
    Json::Reader reader;
    Json::Value obj;
    reader.parse(this->file, obj);
    return obj[parameter];
}


MapFactory::MapFactory(const std::string& mapFile):parser(mapFile) {}

Map MapFactory::create() {
    Json::Value obj = parser.read("map");
    int width_map = obj["width"].asInt();
    int height_map = obj["height"].asInt();
    Map map(width_map,height_map);
    Json::Value& obstacles = obj["obstacles"];// array of characters

    for (auto & i : obstacles){
        int width = i["width"].asInt()/32;
        int height = i["height"].asInt()/32;
        int x = i["x"].asInt() / 32;
        int y = i["y"].asInt() / 32;
        auto* obstacle = new Obstacle(x,y,height,width);
        map.addObstacle(obstacle);
    }

    return map;
}

MapFactory::~MapFactory() = default;


PlayableCharacterFactory::PlayableCharacterFactory(std::string personajesFile,Map& map):parser(personajesFile),map(map) {}

PlayableCharacter PlayableCharacterFactory::create(std::string charRace, std::string charClass) {
    Json::Value obj = parser.read("character");

    int life = 100;
    int x = 1;
    int y = 1;
    int strength = obj["strength"].asInt();
    int agility = obj["agility"].asInt();
    int intelligence = obj["intelligence"].asInt();
    int constitution = obj["constitution"].asInt();
    int raceLifeFactor = obj["race"][charRace]["lifeFactor"].asInt();
    int raceManaFactor = obj["race"][charRace]["manaFactor"].asInt();
    int recoveryFactor = obj["race"][charRace]["recoveryFactor"].asInt();
    int classLifeFactor = obj["class"][charClass]["lifeFactor"].asInt();
    int classManaFactor = obj["class"][charClass]["manaFactor"].asInt();
    int meditationRecoveryFactor = obj["class"][charClass]["meditationRecoveryFactor"].asInt();

    return PlayableCharacter(life,x,y,map,constitution,strength,agility,intelligence,
            raceLifeFactor, classLifeFactor, raceManaFactor, classManaFactor,recoveryFactor,
            meditationRecoveryFactor);
}

PlayableCharacterFactory::~PlayableCharacterFactory() = default;

NpcFactory::NpcFactory(std::string npcsFile,Map& map):parser(npcsFile),map(map) {}

void NpcFactory::create(std::string specie) {
    Json::Value obj = parser.read("npc");

    std::vector<int> possibleLvls = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int level = possibleLvls[rand()%possibleLvls.size()];
    int lifePoints = obj["specie"][specie]["lifePoints"].asInt();
    //HABRIA QUE VER DONDE LIBERAR LA MOVILIDAD , A MI SE ME OCURRIO CREARLA ACA
    Mobility* mobility;
    if (obj["specie"][specie]["mobility"] == "movable") mobility = new Movable;
    else mobility = new NonMovable;
    //Mi idea era asignarle una posicion random al npc cuando se crea
    //Por ahora para hacerlo simple le voy a asignar una pos al azar del vector possibleLvls
    bool isOccupied = true;
    int x, y;
    while(isOccupied) {
        x = possibleLvls[rand()%possibleLvls.size()];
        y = possibleLvls[rand()%possibleLvls.size()];
        Position pos(x, y);
        isOccupied = map.isOccupied(pos);
    }
    std::cout << "La posicion random del npc creado es (" << x << "," << y << ")" << std::endl;
    //CREO QUE PARA EL CASO DEL NPC NO HACE FALTA DEVOLVERLO PORQUE EL CONSTRUCGTOR LO AGREGA SOLO AL MAPA
    Npc(lifePoints, mobility, x, y, map, 0, 0, 0, 0, level, specie);
}

NpcFactory::~NpcFactory() = default;