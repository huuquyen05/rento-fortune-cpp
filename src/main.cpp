#include <iostream>
#include "slot.h"
#include "property.h"
#include "game.h"
#include "player.h"
int main() {
    // 玩家数量输入
    int numPlayers;
    std::cout << "Enter the number of players (2-6): ";
    std::cin >> numPlayers;

    // 检查玩家数量合法性
    if (numPlayers < 2 || numPlayers > 6) {
        std::cerr << "Invalid number of players. The game requires 2-6 players.\n";
        return 1;
    }
    // 初始化游戏
    Game game(numPlayers);
    game.initGame();
    // 游戏主循环
    while (true) {
        if (game.getNumOfPlayers() == 1) {
            std::cout << game.getAllPlayers()[0]->getName() << " is the winner!\n";
            break;
        }
        game.startTurn();
    }
    return 0;
}
