#include "property.h"
#include "slot.h"
#include "iostream"
#include <vector>


Property::Property(std::string name, int price, int type)
    : name(name), price(price), owner(nullptr), level(0), Type(type) {}

// Type 数字对应：1-棕 2-浅蓝 3-浅红 4-橙 5-深红 6-黄 7-绿 8-深蓝 9-火车站 10-水电公司

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
    return Type; // 修正大小写问题
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

std::string Property::payRent(Player* p) {
    // 获取地产的所有者
    Player* owner = getOwner();
    if (owner == nullptr || owner == p) {
        // 如果没有所有者或者玩家自己拥有该地产，则不收费
        return "";
    }

    int numOfSameType = 0;
    
    // 遍历所有的 slots
    for (Slot* slot : slots) {
        // 检查当前 slot 是否是 PropertySlot 类型
        PropertySlot* propertySlot = dynamic_cast<PropertySlot*>(slot);
        if (propertySlot) {
            // 获取 Property 对象
            Property* property = propertySlot->getProperty();
            // 如果这个 Property 的类型和当前 Property 的类型相同且拥有者是当前地产的所有者
            if (property->getType() == Type && property->getOwner() == owner) {
                ++numOfSameType;  // 统计所有者拥有的同类型地产数量
            }
        }
    }

    // 计算租金
    int rent = static_cast<int>(0.1 * price * (1 + level) * (0.5 + numOfSameType * 0.5));

    // 向所有者支付租金
    owner->updateMoney(rent);
    p->updateMoney(-rent);

    std::stringstream sstr;
    sstr << p -> getName() << " paid " << owner -> getName() << " " << rent << " " << "for rent.";
    return sstr.str();
}


std::string Property::utilitypayRent(Player* p) {
    // 获取地产的所有者
    Player* owner = getOwner();
    if (owner == nullptr || owner == p) {
        // 如果没有所有者或者玩家自己拥有该地产，则不收费
        return "";
    }

    int numOfSameType = 0;
    
    // 遍历所有的 slots
    for (Slot* slot : slots) {
        // 检查当前 slot 是否是 PropertySlot 类型
        PropertySlot* propertySlot = dynamic_cast<PropertySlot*>(slot);
        if (propertySlot) {
            // 获取 Property 对象
            Property* property = propertySlot->getProperty();
            // 如果这个 Property 是水电公司并且属于当前所有者
            if (property->getType() == 10 && property->getOwner() == owner) {
                ++numOfSameType;  // 统计所有者拥有的水电公司数量
            }
        }
    }

    // 根据水电公司数量来计算租金
    int rent = 0;
    if (numOfSameType == 1) {
        rent = p->getlaststep() * 4;
    } else if (numOfSameType == 2) {
        rent = p->getlaststep() * 10;
    }

    // 向所有者支付租金
    p->updateMoney(-rent);
    owner->updateMoney(rent);

    std::stringstream sstr;
    sstr << p -> getName() << " paid " << owner -> getName() << " " << rent << " " << "for ultility.";
    return sstr.str();
}


std::string Property::stationpayRent(Player* p) {
    if (owner == nullptr || owner == p) {
        // 如果没有所有者或者玩家自己拥有该车站，则不收费
        return "";
    }

    int ownerStationCount = 0;
    std::vector<int> stationIndices = {5, 15, 25, 35};

    for (int index : stationIndices) {
        if (index >= 0 && index < slots.size()) {
            RailwayStationSlot* railwaySlot = dynamic_cast<RailwayStationSlot*>(slots[index]);
            if (railwaySlot && railwaySlot->getProperty()->getOwner() == owner) {
                ownerStationCount++;
            }
        }
    }

    int rent = 150 * ownerStationCount;
    p->updateMoney(-rent); // 玩家支付租金
    owner->updateMoney(rent); // 所有者收到租金

    // 输出支付信息
    std::cout << p->getName() << " paid " << rent << " rent to " << owner->getName() << " for station.\n";
    std::stringstream sstr;
    sstr << p->getName() << " paid " << rent << " rent to " << owner->getName() << " for station.";
    return sstr.str();
}
