#include "slot.h"
#include "property.h"
#include <iostream>

// 物业格子
PropertySlot::PropertySlot(Property* p) : property(p) {
    name = property->getName();
}

void PropertySlot::landOn(Player& player) {
    if (property->getOwner() == nullptr) {
        // to be continue
        player.buyProperty(property);
    } else {
        property->payRent(player);
    }
}

// 公园格子
ParkSlot::ParkSlot() {
    name = "Park";
}

void ParkSlot::landOn(Player& player) {
    // 公园格子触发的事件，例如获得奖金或其他操作
    std::cout << player.getName() << " landed on Park.\n";
}

// 超税格子
SuperTaxSlot::SuperTaxSlot() {
    name = "Super Tax";
}

void SuperTaxSlot::landOn(Player& player) {
    // 超税格子触发的事件，例如支付超税
    player.updateMoney(-100);  // 假设超税为100
    std::cout << player.getName() << " paid $100 in Super Tax.\n";
}

// 奢侈税格子
LuxuryTaxSlot::LuxuryTaxSlot() {
    name = "Luxury Tax";
}

void LuxuryTaxSlot::landOn(Player& player) {
    // 奢侈税格子触发的事件，例如支付奢侈税
    player.updateMoney(-75);  // 假设奢侈税为75
    std::cout << player.getName() << " paid $75 in Luxury Tax.\n";
}

// 机会卡格子
ChanceSlot::ChanceSlot() {
    name = "Chance";
}

void ChanceSlot::landOn(Player& player) {
    // 机会卡格子触发的事件，例如玩家抽到机会卡
    std::cout << player.getName() << " drew a Chance card.\n";
    // 模拟卡片效果，随机决定事件（这里简单模拟）
    int event = rand() % 5;
    if (event == 0) {
        player.updateMoney(200);  // 假设随机事件，获得200
        std::cout << player.getName() << " won $200 from Chance.\n";
    } else if (event == 1) {
        player.updateMoney(-50);  // 例如，支付50
        std::cout << player.getName() << " paid $50 due to Chance.\n";
    }
}

// 监狱格子
GoToJailSlot::GoToJailSlot() {
    name = "Go to Jail";
}

void GoToJailSlot::landOn(Player& player) {
    // 进入监狱
    player.goToJail();
    std::cout << player.getName() << " has been sent to Jail.\n";
}

// 铁路站格子
RailwayStationSlot::RailwayStationSlot(Property* p) : property(p) {
    name = property->getName();
}

void RailwayStationSlot::landOn(Player& player) {
    if (property->getOwner() == nullptr) {
        // 铁路站未被购买，玩家可以选择购买
        player.buyProperty(property);
    } else {
        // 已有玩家拥有铁路站，支付租金
        property->payRent(player);
    }
}

// 社区宝箱格子
CommunityChestSlot::CommunityChestSlot() {
    name = "Community Chest";
}

void CommunityChestSlot::landOn(Player& player) {
    // 社区宝箱触发的事件，例如玩家抽到社区宝箱卡
    std::cout << player.getName() << " drew a Community Chest card.\n";
    // 模拟卡片效果，随机决定事件（这里简单模拟）
    int event = rand() % 5;
    if (event == 0) {
        player.updateMoney(100);  // 假设获得100
        std::cout << player.getName() << " won $100 from Community Chest.\n";
    } else if (event == 1) {
        player.updateMoney(-50);  // 例如，支付50
        std::cout << player.getName() << " paid $50 due to Community Chest.\n";
    }
}

// 水电公司格子
UtilitySlot::UtilitySlot(Property* p) : property(p) {
    name = property->getName();
}

void UtilitySlot::landOn(Player& player) {
    if (property->getOwner() == nullptr) {
        // 水电公司未被购买，玩家可以选择购买
        player.buyProperty(property);
    } else {
        // 已有玩家拥有水电公司，支付租金
        property->payRent(player);
    }
}
