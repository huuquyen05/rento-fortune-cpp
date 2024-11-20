#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include "player.h"

// Base class for all properties
class Property {
protected:
    std::string name;
    Player *owner;

public:
    Property(std::string name, int type);

    std::string getName();
    int getType();
    Player* getOwner();
    virtual void buyLand(Player *player);
    virtual void payRent(Player *player) = 0; // Pure virtual function
};

// Derived class for normal properties
class NormalProperty : public Property {
private:
    int listOfUpgradeCost[5];
    int listOfRent[5];
    int level;
    int type;

public:
    NormalProperty(std::string name, int costList[], int rentList[], int type);

    void upgrade();
    void buyLand(Player *player) override;
    void payRent(Player *player) override;
};

// Derived class for utilities
class Utility : public Property {
private:
    int baseRentMultiplier; // Multiplier based on dice rolls or owned utilities

public:
    Utility(std::string name, int baseRentMultiplier, int type);

    void buyLand(Player *player) override;
    void payRent(Player *player) override;
};

// Derived class for railroads
class Railroad : public Property {
private:
    int baseRent; // Rent depends on the number of railroads owned

public:
    Railroad(std::string name, int baseRent, int type);

    void buyLand(Player *player) override;
    void payRent(Player *player) override;
};

#endif
