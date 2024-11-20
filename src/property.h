#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include "player.h"

// Base class for all properties
class Property {
protected:
    std::string name;
    Player *owner;
    int price; // only for ultilities (150) and railroads (200)

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
    int baseRentMultiplier = 5; // Multiplier based on dice rolls and number of ultilities owned

public:
    Utility(std::string name);

    void payRent(Player *player) override;
};

// Derived class for railroads
class Railroad : public Property {
private:
    int baseRent = 25; // Rent depends on the number of railroads owned

public:
    Railroad(std::string name);

    void payRent(Player *player) override;
};

#endif
