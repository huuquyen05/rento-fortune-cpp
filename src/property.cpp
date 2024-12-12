#include "property.h"
#include "slot.h"
#include "iostream"

Property::Property(std::string name, int price, int type)
    : name(name), price(price), owner(nullptr), level(0), Type(type){}

//Type数字对应：1-棕 2-浅蓝 3-浅红 4-橙 5-深红 6-黄 7-绿 8-深蓝 9-火车站 10-水电公司

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


void Property::payRent(Player* p){
    // 确认地产是否有所有者
    Player* owner = getOwner();
    if (owner == nullptr || owner == p) {
        // 如果没有所有者或者玩家自己拥有该地产，则不收费
        return;
    }
    int numOfSameType = 0;
    for (Property* index : slots) {
        if (index->getType() == Type && index->getOwner() == owner) {
            ++numOfSameType;
        }
    }// 记录拥有几个同色地块

    int rent = 0.1 * price * (1 + level) * (0.5 + numOfSameType * 0.5);
    owner->updateMoney(rent);
    p->updateMoney(-rent);
}

void Property::utilitypayRent(Player* p){
     // 确认水电是否有所有者
    Player* owner = getOwner();
    if (owner == nullptr || owner == p) {
        // 如果没有所有者或者玩家自己拥有该地产，则不收费
        return;
    }
    int numOfSameType = 0;
    for (Property* index : slots) {
        if (index->getType() == Type && index->getOwner() == owner) {
            ++numOfSameType;
        }
    }// 记录拥有几个同色地块

    if (numOfSameType == 1) {
        p->updateMoney(- p->getlaststep() * 4);
        owner->updateMoney( p->getlaststep() * 4);
    }else {
        p->updateMoney(- p->getlaststep() * 10);
        owner->updateMoney( p->getlaststep() * 10);
    }
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
