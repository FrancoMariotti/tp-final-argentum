#ifndef ARGENTUM_FACTORY_H
#define ARGENTUM_FACTORY_H

#include <fstream>
#include <jsoncpp/json/value.h>
#include "string"
#include "Observer.h"
#include "NormalWeapon.h"

class Game;
class Map;

class FileParser {
    std::ifstream file;
public:
    explicit FileParser(const std::string &filename);
    Json::Value read(const std::string& parameter);

};

class MapFactory {
    std::string file;
    Json::Value mapObj;
    public:
        explicit MapFactory(const std::string& configFile);
        Map* create();
        ~MapFactory();
};

class PlayableCharacterFactory {
    Json::Value characterObj;
    public:
        explicit PlayableCharacterFactory(const std::string& configFile);
        void create(Map* map,const std::string& playerName,const std::string& charRace,
                const std::string& charClass, Observer* observer);
        ~PlayableCharacterFactory();
};

class NpcFactory {
    int counter;
    Json::Value npcsObj;
    public:
        explicit NpcFactory(const std::string& configFile);
        void create(Map* map,const std::string& specie,Observer* observer);
        ~NpcFactory();
};

class EquippableFactory {
public:
    virtual Equippable* create(std::string configFile,std::string itemName,int cost)= 0;
    virtual ~EquippableFactory() = default;
};

class NormalWeaponFactory : public EquippableFactory {
public:
    Equippable* create(std::string configFile,std::string itemName,int cost) override;
};

class RangeWeaponFactory : public EquippableFactory{
public:
    Equippable* create(std::string configFile,std::string itemName,int cost) override;
};

class ProtectionFactory : public EquippableFactory {
public:
    Equippable * create(std::string configFile, std::string itemName, int cost) override;
};

class LifePotionFactory : public EquippableFactory {
public:
    Equippable * create(std::string configFile, std::string itemName, int cost) override;
};

class ManaPotionFactory : public EquippableFactory {
public:
    Equippable * create(std::string configFile, std::string itemName, int cost) override;
};

class MagicalWeaponFactory : public EquippableFactory {
public:
    Equippable * create(std::string configFile, std::string itemName, int cost) override;
};

#endif //ARGENTUM_FACTORY_H
