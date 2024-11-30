#ifndef SLOT_H
#define SLOT_H

#include <string>
#include "player.h"

class Slot {
protected:
    std::string name;

public:
    virtual void landOn(Player& player) = 0;  // 玩家到达该格子时触发事件
    virtual std::string getName() const { return name; }
};

class PropertySlot : public Slot {
private:
    Property* property;

public:
    PropertySlot(Property* p);
    void landOn(Player& player) override;
};

#endif
