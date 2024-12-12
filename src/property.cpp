#include "property.h"

Property::Property(std::string name, int price)
    : name(name), price(price), owner(nullptr), level(0) {}

std::string Property::getName() const {
    return name;
}

int Property::getPrice() const {
    return price;
}

int Property::getLevel() const {
    return level;
}

Player* Property::getOwner() const {
    return owner;
}

void Property::setOwner(Player* player) {
    owner = player;
}

void Property::upgrade() {
    ++level;
}

void Property::changePrice(int NewPrice) {
    price = NewPrice;
}

void Property::payRent(Player* p){
    
}