#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include "player.h"

class Property {
protected:
    std::string name;
    int price;
    Player* owner;  // 物业的拥有者
    int level;

public:
    Property(std::string name, int price);
    std::string getName() const;
    int getPrice() const;
    int getLevel() const;
    Player* getOwner() const;
    void setOwner(Player* player);
    void upgrade();
    virtual void payRent(Player& player) = 0;  // 纯虚函数，派生类需要实现
};

#endif