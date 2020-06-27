#ifndef ARGENTUM_BANKER_H
#define ARGENTUM_BANKER_H
#include "map"

class Banker {
    std::map<std::string,int> accounts;
public:
    void registerAccount(const std::string &playerName, int initialDeposit);
    void deposit(const std::string &playerName, int deposit);
};


#endif //ARGENTUM_BANKER_H
