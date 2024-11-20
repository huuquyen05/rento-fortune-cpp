#ifndef property_h
#define property_h

#include <string>
#include "player.h"

class Property {
private:
    std::string name;
    int listOfUpgradeCost[5];
    int listOfRent[5];
    Player *owner;
    int level;
    int type;

public:
    Property(std::string name, int costList[], int rentList[], int type);

    std::string getName();
    int getType();
    void upgrade();
    void buyLand(Player *player);
    void payRent(Player *player);
};

#endif