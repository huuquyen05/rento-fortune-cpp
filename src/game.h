#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
class Player;
class Slot;


class Game {
private:
    std::vector<Player*> players;  // 所有玩家
    std::vector<Slot*> board;  // 棋盘上的格子
    int currentPlayerIndex;  // 当前玩家的索引

public:
    Game(int numPlayers);
    Game(std::string names[4]);
    void initGame();
    int getCurPlayer();
    void startTurn();
    std::pair<int, int> rollDice();
    void processTurn();
    void checkBankruptcy();
    void nextPlayer();
    std::vector<Player*> getAllPlayers(); //获取所有玩家
    int getNumOfPlayers(); //获取玩家人数
};

#endif
