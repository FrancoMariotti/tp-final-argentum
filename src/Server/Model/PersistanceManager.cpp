//
// Created by franco on 19/7/20.
//

#include "PersistanceManager.h"

#include <utility>
#include <fstream>
#include <Common/OsException.h>
#include "Configuration.h"
#include "Server/Model/Character/PlayableCharacter.h"
#include "Server/Model/Character/LifeState.h"

PersistanceManager::PersistanceManager(std::string playersInfoMapFile,
        std::string playersInfoFile) : playersInfoMapFile(std::move(playersInfoMapFile)),
        playersInfoFile(std::move(playersInfoFile)) , config(Configuration::getInstance()){

    std::fstream playersInfoMapStream(this->playersInfoMapFile, std::fstream::in | std::fstream::out | std::fstream::binary);
    //Chequeo que los archivos se hayan podido abrir
    if (!playersInfoMapStream) {
        throw OSError("Error al abrir los archivos binarios de informacion de los jugadores");
    }

    int nameLength, index, passwordLength;
    while (playersInfoMapStream.read((char*)&nameLength, sizeof(int))) {
        char* name = new char[nameLength + 1];
        playersInfoMapStream.read(name, nameLength);
        name[nameLength] = '\0';
        playersInfoMapStream.read((char*)&passwordLength, sizeof(int));
        char* password = new char[passwordLength + 1];
        playersInfoMapStream.read(password, passwordLength);
        password[passwordLength] = '\0';
        playersInfoMapStream.read((char*)&index, sizeof(int));
        login_info_t info = {password, index};
        if (playersInfoMapStream.good()) playersInfoMap[name] = info;
        delete[] name;
        delete[] password;
    }

    playersAmount = playersInfoMap.size();
    playersInfoMapStream.close();
}

void PersistanceManager::persistPlayerData(PlayableCharacter *pCharacter) {
    //Busco en el mapa el index que le corresponde al jugador
    int index = playersInfoMap[pCharacter->id].index;
    //Guardo los identificadores de los items que tiene el usuario en su armadura,
    //inventario y cuenta de banco
    std::vector<int> armourIds, inventoryIds, accountIds;
    for (auto &protection : pCharacter->armour.protections) {
        armourIds.push_back(protection->getId());
    }

    for (auto &inventoryItem : pCharacter->inventory.elements) {
        inventoryIds.push_back(inventoryItem->getId());
    }

    for (auto &bankItem : pCharacter->bankAccount.items) {
        accountIds.push_back(bankItem->getId());
    }
    int lifeStateInt = pCharacter->lifeState->convertToInt();
    //Creo el struct con la informacion del jugador
    character_info_t characterInfo = {(int)pCharacter->lifePoints, pCharacter->level,
                                      pCharacter->constitution, pCharacter->agility, pCharacter->strength,
                                      pCharacter->intelligence, pCharacter->raceLifeFactor, pCharacter->classLifeFactor,
                                      pCharacter->raceManaFactor, pCharacter->classManaFactor, pCharacter->recoveryFactor,
                                      pCharacter->meditationRecoveryFactor, pCharacter->currPos.getX(),
                                      pCharacter->currPos.getY(), (int)pCharacter->mana, pCharacter->gold, pCharacter->xp,
                                      inventoryIds, pCharacter->activeWeapon->getId(), armourIds, lifeStateInt,
                                      pCharacter->inCity, pCharacter->bankAccount.gold, accountIds, pCharacter->raceId};
    //Escribo el struct en el archivo de informacion de los jugadores
    addPlayerInfoToFile(characterInfo, index);
}

void PersistanceManager::addPlayerInfoToFile(character_info_t playerInfo, int index) {
    std::fstream infoStream(playersInfoFile, std::fstream::out | std::fstream::binary | std::fstream::in);
    if (!infoStream) {
        throw OSError("Error al abrir los archivos binarios de informacion de los jugadores");
    }
    //situo el puntero para sobreescribir el elemento en el index correcto
    //infoStream.seekp(sizeof(character_info_t) * index);
    infoStream.seekp(sizeof(int) * CHARACTER_INFO_INTS_AMOUNT * index);

    infoStream.write((char*)&playerInfo.lifePoints, sizeof(int));
    infoStream.write((char*)&playerInfo.level, sizeof(int));
    infoStream.write((char*)&playerInfo.constitution, sizeof(int));
    infoStream.write((char*)&playerInfo.agility, sizeof(int));
    infoStream.write((char*)&playerInfo.strength, sizeof(int));
    infoStream.write((char*)&playerInfo.intelligence, sizeof(int));
    infoStream.write((char*)&playerInfo.raceLifeFactor, sizeof(int));
    infoStream.write((char*)&playerInfo.classLifeFactor, sizeof(int));
    infoStream.write((char*)&playerInfo.raceManaFactor, sizeof(int));
    infoStream.write((char*)&playerInfo.classManaFactor, sizeof(int));
    infoStream.write((char*)&playerInfo.recoveryFactor, sizeof(int));
    infoStream.write((char*)&playerInfo.meditationRecoveryFactor, sizeof(int));
    infoStream.write((char*)&playerInfo.x, sizeof(int));
    infoStream.write((char*)&playerInfo.y, sizeof(int));
    infoStream.write((char*)&playerInfo.mana, sizeof(int));
    infoStream.write((char*)&playerInfo.gold, sizeof(int));
    infoStream.write((char*)&playerInfo.xp, sizeof(int));
    for (unsigned int j = 0; j < (unsigned)config.constants["inventoryMaxItems"] ; ++j) {
        if (j < playerInfo.inventoryItems.size())
            infoStream.write((char*)&playerInfo.inventoryItems[j], sizeof(int));
        else {
            int zero = 0;
            infoStream.write((char*)&zero, sizeof(int));
        }
    }
    infoStream.write((char*)&playerInfo.activeWeapon, sizeof(int));
    for (unsigned int j = 0; j < (unsigned)config.constants["armourMaxItems"]; ++j) {
        infoStream.write((char*)&playerInfo.protections[j], sizeof(int));
    }
    infoStream.write((char*)&playerInfo.lifeState, sizeof(int));
    infoStream.write((char*)&playerInfo.inCity, sizeof(int));
    infoStream.write((char*)&playerInfo.goldInBank, sizeof(int));
    for (unsigned int j = 0; j < (unsigned)config.constants["accountMaxItems"] ; ++j) {
        if (j < playerInfo.itemsInBank.size())
            infoStream.write((char*)&playerInfo.itemsInBank[j], sizeof(int));
        else {
            int zero = 0;
            infoStream.write((char*)&zero, sizeof(int));
        }
    }
    infoStream.write((char*)&playerInfo.race, sizeof(int));
    infoStream.close();
}

character_info_t PersistanceManager::getPlayerInfoFromFile(int index) {
    character_info_t characterInfo;
     std::fstream infoStream(playersInfoFile, std::fstream::in | std::fstream::binary);
     if (!infoStream) {
        throw OSError("Error al abrir los archivos binarios de informacion de los jugadores");
     }
     //situo el puntero para leer el elemento en el index correcto
     infoStream.seekg(sizeof(character_info_t) * index);
     //comienzo a guardar la informacion
     infoStream.read((char*)&characterInfo.lifePoints, sizeof(int));
     infoStream.read((char*)&characterInfo.level, sizeof(int));
     infoStream.read((char*)&characterInfo.constitution, sizeof(int));
     infoStream.read((char*)&characterInfo.agility, sizeof(int));
     infoStream.read((char*)&characterInfo.strength, sizeof(int));
     infoStream.read((char*)&characterInfo.intelligence, sizeof(int));
     infoStream.read((char*)&characterInfo.raceLifeFactor, sizeof(int));
     infoStream.read((char*)&characterInfo.classLifeFactor, sizeof(int));
     infoStream.read((char*)&characterInfo.raceManaFactor, sizeof(int));
     infoStream.read((char*)&characterInfo.classManaFactor, sizeof(int));
     infoStream.read((char*)&characterInfo.recoveryFactor, sizeof(int));
     infoStream.read((char*)&characterInfo.meditationRecoveryFactor, sizeof(int));
     infoStream.read((char*)&characterInfo.x, sizeof(int));
     infoStream.read((char*)&characterInfo.y, sizeof(int));
     infoStream.read((char*)&characterInfo.mana, sizeof(int));
     infoStream.read((char*)&characterInfo.gold, sizeof(int));
     infoStream.read((char*)&characterInfo.xp, sizeof(int));
     for (unsigned int j = 0; j < (unsigned)config.constants["inventoryMaxItems"] ; ++j) {
         int currValue;
         infoStream.read((char*)&currValue, sizeof(int));
         characterInfo.inventoryItems.push_back(currValue);
     }
     infoStream.read((char*)&characterInfo.activeWeapon, sizeof(int));
     for (unsigned int j = 0; j < (unsigned)config.constants["armourMaxItems"] ; ++j) {
         int currValue;
         infoStream.read((char*)&currValue, sizeof(int));
         characterInfo.protections.push_back(currValue);
     }
     infoStream.read((char*)&characterInfo.lifeState, sizeof(int));
     infoStream.read((char*)&characterInfo.inCity, sizeof(int));
     infoStream.read((char*)&characterInfo.goldInBank, sizeof(int));
     for (unsigned int j = 0; j < (unsigned)config.constants["accountMaxItems"]; ++j) {
         int currValue;
         infoStream.read((char*)&currValue, sizeof(int));
         characterInfo.itemsInBank.push_back(currValue);
     }
     infoStream.read((char*)&characterInfo.race, sizeof(int));
     infoStream.close();
     return characterInfo;
}

bool PersistanceManager::login(const std::string &playerName, std::string &password,
        Map* map, Observer* observer, PlayableCharacterFactory& pcFactory) {
    if (playersInfoMap.find(playerName) != playersInfoMap.end()) {
        if (playersInfoMap.at(playerName).password == password) {
            int index = playersInfoMap.at(playerName).index;
            character_info_t characterInfo = getPlayerInfoFromFile(index);
            pcFactory.createPlayerFromInfo(characterInfo, playerName, map, observer);
            return true;
        }
    }
    return false;
}
bool PersistanceManager::existsUser(const std::string &username) {
    return playersInfoMap.find(username) == playersInfoMap.end();
}

void PersistanceManager::signup(const std::string &username, const std::string &password) {
    std::fstream playersInfoMapStream(playersInfoMapFile, std::fstream::in | std::fstream::out | std::fstream::binary);
    //Chequeo que el archivo se hayan podido abrir
    if (!playersInfoMapStream) {
        throw OSError("Error al abrir los archivos binarios de informacion de los jugadores");
    }
        //Agrego el index y la contrasenia del jugador al archivo del mapa y al mapa.
    uint32_t nameLen = username.size();
    uint32_t passwordLen = password.size();
    playersInfoMapStream.seekp(0, std::ios_base::end);

    playersInfoMapStream.write((char*)&nameLen, sizeof(uint32_t));
    playersInfoMapStream.write(username.c_str(), nameLen);

    playersInfoMapStream.write((char*)&passwordLen, sizeof(uint32_t));
    playersInfoMapStream.write(password.c_str(), passwordLen);

    playersInfoMapStream.write((char*)&playersAmount, sizeof(uint32_t));

    login_info_t info = {password, playersAmount};
    playersInfoMap[username] = info;
    playersAmount++;
    playersInfoMapStream.close();
}