#include "property.h"
#include "iostream"

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

void Property::utilitypayRent(Player* p){
    p->updateMoney(- p->getlaststep() * 4);
}

void Property::stationpayRent(Player* p) {
    // 确认车站是否有所有者
    Player* owner = getOwner();
    if (owner == nullptr || owner == p) {
        // 如果没有所有者或者玩家自己拥有该车站，则不收费
        return;
    }

    // 统计所有者拥有的车站数量
    int ownerStationCount = 0;
    
    // 车站格子下标固定为 5, 15, 25, 35
    std::vector<int> stationIndices = {5, 15, 25, 35};
    
    for (int index : stationIndices) {
        RailwayStationSlot* railwaySlot = dynamic_cast<RailwayStationSlot*>(slots[index]);
        if (railwaySlot && railwaySlot->getProperty()->getOwner() == owner) {
            // 如果该车站是所有者拥有的，增加车站数量
            ownerStationCount++;
        }
    }

    // 计算租金：150 * 所有者拥有的车站数量
    int rent = 150 * ownerStationCount;

    // 向所有者支付租金
    p->updateMoney(-rent);  // 玩家支付租金
    owner->updateMoney(rent);  // 所有者收到租金

    // 输出支付信息
    std::cout << p->getName() << " paid " << rent << " rent to " << owner->getName() << " for station.\n";
}
