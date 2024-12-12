#ifndef SLOT_H
#define SLOT_H

#include <string>
#include "player.h"
#include "property.h"

// 基础 Slot 类
class Slot {
protected:
    std::string name;  // 格子的名称

public:
    virtual void landOn(Player* player, std::vector<Player*>& allPlayers) = 0;  // 玩家落到该格子时触发的操作
    virtual std::string getName() const { return name; }  // 获取格子的名称
};

// 物业格子类
class PropertySlot : public Slot {
private:
    Property* property;

public:
    PropertySlot(Property* p);
    void landOn(Player* player, std::vector<Player*>& allPlayers) override;
    Property* getProperty(){
        return property;
    }
};

// 公园格子
class ParkSlot : public Slot {
public:
    ParkSlot();
    void landOn(Player* player, std::vector<Player*>& allPlayers) override;
};

// 超税格子
class SuperTaxSlot : public Slot {
public:
    SuperTaxSlot();
    void landOn(Player* player, std::vector<Player*>& allPlayers) override;
};

// 奢侈税格子
class LuxuryTaxSlot : public Slot {
public:
    LuxuryTaxSlot();
    void landOn(Player* player, std::vector<Player*>& allPlayers) override;
};

// 机会卡格子
class ChanceSlot : public Slot {
public:
    ChanceSlot();
    void landOn(Player* player, std::vector<Player*>& allPlayers) override;
};

// 监狱格子
class GoToJailSlot : public Slot {
public:
    GoToJailSlot();
    void landOn(Player* player, std::vector<Player*>& allPlayers) override;
};

// 铁路站格子
class RailwayStationSlot : public Slot {
private:
    Property* property;

public:
    RailwayStationSlot(Property* p);
    void landOn(Player* player, std::vector<Player*>& allPlayers) override;
    Property* getProperty(){
        return property;
    }
};

// 社区宝箱格子
class CommunityChestSlot : public Slot {
public:
    CommunityChestSlot();
    void landOn(Player* player, std::vector<Player*>& allPlayers) override;
};

// 水电公司格子
class UtilitySlot : public Slot {
private:
    Property* property;
    Property* getProperty(){
        return property;
    }

public:
    UtilitySlot(Property* p);
    void landOn(Player* player, std::vector<Player*>& allPlayers) override;
};
extern std::vector<Slot*> slots;

#endif

// park, super tax, luxury tax, chance, go to jail, railway station, community chest, water works, electricity company