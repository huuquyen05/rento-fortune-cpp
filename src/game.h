#ifndef GAME_H
#define GAME_H

#include <vector>
class Player;
class Slot;


class Game {
private:
    std::vector<Player*> players;  // 所有玩家
    std::vector<Slot*> board;  // 棋盘上的格子
    int currentPlayerIndex;  // 当前玩家的索引

public:
    Game(int numPlayers);
    void initGame();
    int getCurPlayer();
    void startTurn();
    void rollDice();
    void processTurn();
    void checkBankruptcy();
    void nextPlayer();
    std::vector<Player*> getAllPlayers(); //获取所有玩家
    int getNumOfPlayers(); //获取玩家人数
};

#endif
