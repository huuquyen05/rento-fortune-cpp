#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "property.h"

class Player {
private:
    std::string name;
    int money;
    std::vector<Property*> properties;  // 玩家拥有的物业
    bool inJail;
    bool bankrupt;
    int position;  // 玩家当前在棋盘上的位置
    int colourOfToken;  // 玩家棋子颜色（可选）
    int playerIndex;

public:
    Player(std::string name, int initialMoney = 1500, int tokenColor = 0, int pI);
    
    // 获取玩家信息
    std::string getName() const;
    int getMoney() const;
    int getPosition() const;
    int getColourOfToken() const;
    int getPlayerIndex() const;
    // 玩家操作
    void updateMoney(int amount);  // 修改玩家资金
    void move(int steps);  // 玩家根据骰子步数移动
    void buyProperty(Property* property);  // 玩家购买物业
    bool isInJail() const;  // 检查玩家是否在监狱
    void goToJail();  // 把玩家送到监狱
    void getOutOfJail();  // 让玩家脱离监狱
    bool isBankrupt() const;  // 检查玩家是否破产
    void goBankrupt();  // 玩家破产，退出游戏
    void addProperty(Property* property);  // 增加一个物业
};

#endif
