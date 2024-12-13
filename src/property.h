#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
class Player;

class Property {
protected:
    std::string name;
    int price;
    Player* owner;  // 物业的拥有者
    int level;
    int Type;

public:
    Property(std::string name, int price, int Type);
    std::string getName() const;
    int getPrice() const;
    int getLevel() const;
    int getType() const;
    Player* getOwner() const;
    void setOwner(Player* player);
    void upgrade();
    void payRent(Player* p);
    void utilitypayRent(Player* p);
    void stationpayRent(Player* p);
};

#endif