#include "property.h"

Property::Property(std::string name, int price)
    : name(name), price(price), owner(nullptr) {}

std::string Property::getName() const {
    return name;
}

int Property::getPrice() const {
    return price;
}

Player* Property::getOwner() const {
    return owner;
}

void Property::setOwner(Player* player) {
    owner = player;
}
