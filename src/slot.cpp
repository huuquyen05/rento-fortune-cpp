#include "slot.h"
#include "property.h"
#include <iostream>
std::vector<Slot*> slots;

std::string Slot::getName() {
    return this -> name;
}

// 物业格子
PropertySlot::PropertySlot(Property* p) : property(p) {
    name = property->getName();
}

void PropertySlot::landOn(Player* player, std::vector<Player*>& allPlayers) {
    if (property->getOwner() == nullptr) {
        // to be continue
        player->buyProperty(property);
    } else {
        property->payRent(player);
    }
}

std::string PropertySlot::getDescription() {
    return name + "\n" + "Price：" + std::to_string(property->getPrice()) + "\n" + "Upgrade Price：" + std::to_string(property->getPrice()/2) + "\n" + std::to_string(property->getLevel()) + "\n" + property->getOwner()->getName() + "\n" + "Property";
}

std::string PropertySlot::getOwner() {
    return property->getOwner()->getName();
}

int PropertySlot::getLevel() {
    return property->getLevel();
}

// 停车场格子
ParkSlot::ParkSlot() {
    name = "Free Parking";
}

void ParkSlot::landOn(Player* player, std::vector<Player*>& allPlayers) {
    // 公园格子触发的事件，例如获得奖金或其他操作
    std::cout << player->getName() << " landed on Park.\n";
}

std::string ParkSlot::getDescription() {
    return name;
}

// 超税格子
SuperTaxSlot::SuperTaxSlot() {
    name = "Super Tax";
}

void SuperTaxSlot::landOn(Player* player, std::vector<Player*>& allPlayers) {
    // 超税格子触发的事件，例如支付超税
    player->updateMoney(-100);  // 假设超税为100
    std::cout << player->getName() << " paid $100 in Super Tax.\n";
}

std::string SuperTaxSlot::getDescription() {
    return name + "\n" + "Super Tax：100";
}

// 奢侈税格子
LuxuryTaxSlot::LuxuryTaxSlot() {
    name = "Luxury Tax";
}

void LuxuryTaxSlot::landOn(Player* player, std::vector<Player*>& allPlayers) {
    // 奢侈税格子触发的事件，例如支付奢侈税
    player->updateMoney(-75);  // 假设奢侈税为75
    std::cout << player->getName() << " paid $75 in Luxury Tax.\n";
}

std::string LuxuryTaxSlot::getDescription() {
    return name + "\n" + "Luxury Tax：75";
}

// 监狱格子
GoToJailSlot::GoToJailSlot() {
    name = "Go to Jail";
}

void GoToJailSlot::landOn(Player* player, std::vector<Player*>& allPlayers) {
    // 进入监狱
    player->goToJail();
    std::cout << player->getName() << " has been sent to Jail.\n";
}

std::string GoToJailSlot::getDescription() {
    return name;
}

// 铁路站格子
RailwayStationSlot::RailwayStationSlot(Property* p) : property(p) {
    name = property->getName();
}

void RailwayStationSlot::landOn(Player* player, std::vector<Player*>& allPlayers) {
    if (property->getOwner() == nullptr) {
        // 铁路站未被购买，玩家可以选择购买
        player->buyProperty(property);
    } else {
        // 已有玩家拥有铁路站，支付租金
        property->stationpayRent(player);
    }
}

std::string RailwayStationSlot::getDescription() {
    return name + "\n" + "Price：" + std::to_string(property->getPrice()) + "\n" + property->getOwner()->getName() + "\n" + "Railway Station";
}

std::string RailwayStationSlot::getOwner() {
    return property->getOwner()->getName();
}

int RailwayStationSlot::getLevel() {
    return property->getLevel();
}

// 机会卡格子
ChanceSlot::ChanceSlot() {
    name = "Chance";
}

void ChanceSlot::landOn(Player* player, std::vector<Player*>& allPlayers) {
    // 机会卡触发的事件，例如玩家抽到机会卡
    std::cout << player->getName() << " drew a Chance card.\n";
    
    // 随机决定触发的卡片
    int event = rand() % 15;  // 假设有15种不同的机会卡事件
    switch (event) {
        case 0:
            player->moveto(0); // 前进到“Go”
            std::cout << player->getName() << " advanced to 'Go' and received $200.\n";
            break;
        case 1:
            // 前进到 Trafalgar Square，经过“Go”时，额外获得200美元
            std::cout << player->getName() << " advanced to Trafalgar Square. If you pass 'Go', you collect $200.\n";
            player->moveto(13);
            break;
        case 2:
            // 前进到 Pall Mall，经过“Go”时，额外获得200美元
            std::cout << player->getName() << " advanced to Pall Mall. If you pass 'Go', you collect $200.\n";
            player->moveto(24);
            break;
        case 3:
            // 前进到最近的公用设施
            std::cout << player->getName() << " advanced to the nearest Utility.\n";
            if (player->getPosition() < 12 || player->getPosition() > 28) {
                player->moveto(12);
                slots[12]->landOn(player, players);
            } else {
                player->moveto(28);
                slots[28]->landOn(player, players);
            }
            // 这里我们假设玩家会选择购买或者支付租金，具体逻辑依赖于游戏规则
            
            break;
        case 4:
            // 前进到最近的铁路
            std::cout << player->getName() << " advanced to the nearest Railroad.\n";
            if (player->getPosition() < 5 || player->getPosition() > 35) {
                player->moveto(5);
                slots[5]->landOn(player, players);
            } else if (player->getPosition() > 5 && player->getPosition() < 15) {
                player->moveto(15);
                slots[15]->landOn(player, players);
            } else if (player->getPosition() > 15 && player->getPosition() < 25) {
                player->moveto(25);
                slots[25]->landOn(player, players);
            } else {
                player->moveto(35);
                slots[35]->landOn(player, players);
            }
            // 购买或支付租金的逻辑
            break;
        case 5:
            player->updateMoney(50); 
            std::cout << player->getName() << " received a dividend of $50 from the bank.\n";
            break;
        case 6:
            // 获取一张"出狱免费卡"（需要实现卡片存储逻辑）
            player->haveoutJailcard();
            std::cout << player->getName() << " received a 'Get out of Jail Free' card.\n";
            break;
        case 7:
            std::cout << player->getName() << " goes directly to Jail. (Cannot collect $200 from 'Go')\n";
            player->goToJail();  
            break;
        case 8:
            std::cout << player->getName() << " must make general repairs on all properties.\n";
            player->updateMoney(-25 * player->getNumberOfHouses() - 100 * player->getNumberOfHotels());
            
            break;
        case 9:
            std::cout << player->getName() << " took a ride to King's Cross Station.\n";
            player->moveto(25);
            break;
        case 10:
            player->updateMoney(-15);  
            std::cout << player->getName() << " paid Poor Tax of $15.\n";
            break;
        case 11:
            std::cout << player->getName() << " advanced to Mayfair.\n";
            player->moveto(39);
            break;
        case 12:
            player->updateMoney(-50 * (player->getNumberOfPlayers() - 1));
            //需要给别的玩家付钱
            std::cout << player->getName() << " has been elected Chairman of the Board. Pay each player $50.\n";
            break;
        case 13:
            player->updateMoney(150);  
            std::cout << player->getName() << " collected $150 from building and loan maturity.\n";
            break;
        default:
            std::cout << player->getName() << " drew a Chance card with no effect.\n";
    }
}

std::string ChanceSlot::getDescription() {
    return name;
}

// 水电公司格子
UtilitySlot::UtilitySlot(Property* p) : property(p) {
    name = property->getName();
}

void UtilitySlot::landOn(Player* player, std::vector<Player*>& allPlayers) {
    if (property->getOwner() == nullptr) {
        // 水电公司未被购买，玩家可以选择购买
        player->buyProperty(property);
    } else {
        // 已有玩家拥有水电公司，支付租金
        property->utilitypayRent(player);
    }
}

std::string UtilitySlot::getDescription() {
    return name + "\n" + "Price：" + std::to_string(property->getPrice()) + "\n" + property->getOwner()->getName() + "\n" + "Utility";
}

std::string UtilitySlot::getOwner() {
    return property->getOwner()->getName();
}

int UtilitySlot::getLevel() {
    return property->getLevel();
}

CommunityChestSlot::CommunityChestSlot() {
    name = "Community Chest";
}

void CommunityChestSlot::landOn(Player* player, std::vector<Player*>& allPlayers) {
    std::cout << player->getName() << " drew a Community Chest card.\n";
    
    // 随机决定触发的卡片
    int event = rand() % 17;  // 假设有17种不同的社区宝箱事件
    // 在 switch 语句外部初始化
    int houses = player->getNumberOfHouses();  // 获取玩家的房子数量
    int hotels = player->getNumberOfHotels();  // 获取玩家的酒店数量

    switch (event) {
        case 0:
            player->moveto(0);  // 前进到“Go”，获得200美元
            std::cout << player->getName() << " advanced to 'Go' and received $200.\n";
            break;
        case 1:
            player->updateMoney(200);  // 银行错误，获得200美元
            std::cout << player->getName() << " received $200 from a bank error.\n";
            break;
        case 2:
            player->updateMoney(-50);  // 医生费用，支付50美元
            std::cout << player->getName() << " paid $50 for doctor's fees.\n";
            break;
        case 3:
            player->updateMoney(50);  // 股票销售，获得50美元
            std::cout << player->getName() << " received $50 from the sale of stock.\n";
            break;
        case 4:
            // 获取“出狱免费卡” (此部分需要玩家类实现“出狱免费卡”功能)
            player->haveoutJailcard();
            std::cout << player->getName() << " received a 'Get out of Jail Free' card.\n";
            break;
        case 5:
            // 直接进监狱
            std::cout << player->getName() << " goes directly to Jail (Cannot collect $200 from 'Go').\n";
            player->goToJail();  // 假设Player类有putInJail()方法
            break;
        case 6:
            // 向每个玩家收取50美元，模拟“Grand Opera Night”
            std::cout << player->getName() << " collects $50 from each player for Grand Opera Night.\n";
            for (auto p : allPlayers) {
                if (p->getName() != player->getName()) {
                    p->updateMoney(-50);
                    player->updateMoney(50);
                }
            }
            break;
        case 7:
            player->updateMoney(100);  // 假设Holiday Fund获得100美元
            std::cout << player->getName() << " collected $100 from Holiday Fund.\n";
            break;
        case 8:
            player->updateMoney(20);  // 收到税务退还20美元
            std::cout << player->getName() << " received an income tax refund of $20.\n";
            break;
        case 9:
            player->updateMoney(40);  // 假设Birthday获得40美元
            std::cout << player->getName() << " collected $40 on Birthday.\n";
            break;
        case 10:
            player->updateMoney(100);  // 生命保险支付100美元
            std::cout << player->getName() << " received $100 from life insurance.\n";
            break;
        case 11:
            player->updateMoney(-50);  // 医院费用支付50美元
            std::cout << player->getName() << " paid $50 for hospital fees.\n";
            break;
        case 12:
            player->updateMoney(-50);  // 学校费用支付50美元
            std::cout << player->getName() << " paid $50 for school fees.\n";
            break;
        case 13:
            player->updateMoney(25);  // 咨询费，获得25美元
            std::cout << player->getName() << " received $25 from consultancy fee.\n";
            break;
        case 14:
            // 道路维修费用，按房子数量计算
            std::cout << player->getName() << " is assessed for street repairs. Pay $40 per house and $115 per hotel.\n";
            player->updateMoney(-(40 * houses + 115 * hotels));  // 使用外部初始化的变量
            break;
        case 15:
            player->updateMoney(10);  // 美容大赛，获得10美元
            std::cout << player->getName() << " won second prize in a beauty contest and received $10.\n";
            break;
        case 16:
            player->updateMoney(100);  // 继承100美元
            std::cout << player->getName() << " inherited $100.\n";
            break;
        default:
            std::cout << player->getName() << " drew a Community Chest card with no effect.\n";
            break;
    }

}

std::string CommunityChestSlot::getDescription() {
    return name;
}
