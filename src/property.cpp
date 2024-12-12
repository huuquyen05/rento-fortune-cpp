#include "property.h"

Property::Property(std::string name, int price, int type)
    : name(name), price(price), owner(nullptr), level(0), type(0){}

//type数字对应：1-棕 2-浅蓝 3-浅红 4-橙 5-深红 6-黄 7-绿 8-深蓝 9-火车站 10-水电公司

std::string Property::getName() const {
    return name;
}

int Property::getPrice() const {
    return price;
}

int Property::getLevel() const {
    return level;
}

int Property::getType() const {
    return type;
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

void Property::utilitypayRent(Player* p){

}

void Property::stationpayRent(Player* p){

}