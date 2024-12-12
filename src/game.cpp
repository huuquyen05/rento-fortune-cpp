#include "game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

Game::Game(int numPlayers) : currentPlayerIndex(0) {
    for (int i = 0; i < numPlayers; ++i) {
        players.push_back(new Player("Player " + std::to_string(i + 1)));
    }

    // 初始化棋盘
    
    // 可以继续添加更多格子...
}

vector<Player*> getAllPlayers() {
    return players; //获取所有玩家，用于机会卡
}

int getNumOfPlayers() {
    return players.size(); //获取玩家总数
}

void Game::initGame() {
    srand(time(0));  // 随机种子
    // 初始化其他游戏设置（比如洗牌卡片等）
}

void Game::startTurn() {
    Player* currentPlayer = players[currentPlayerIndex];
    std::cout << currentPlayer->getName() << "'s turn\n";
    rollDice();
    processTurn();
}

void Game::rollDice() {
    int dice1 = rand() % 6 + 1;  // 随机掷骰子
    int dice2 = rand() % 6 + 1;
    std::cout << "Rolled: " << dice1 << " and " << dice2 << "\n";
    if (players[currentPlayerIndex]->isInJail() == false) {
        players[currentPlayerIndex]->move(dice1 + dice2);
    }else {
        players[currentPlayerIndex]->isInJail() = (dice1 == dice2) ? false : true; //在监狱里的判断
    }
}

void Game::processTurn() {
    Player* currentPlayer = players[currentPlayerIndex];
    Slot* currentSlot = board[currentPlayer->getPosition()];
    std::cout << currentPlayer->getName() << " landed on " << currentSlot->getName() << "\n";
    currentSlot->landOn(*currentPlayer);
    checkBankruptcy();
    nextPlayer();
}

void Game::checkBankruptcy() {
    Player* currentPlayer = players[currentPlayerIndex];
    if (currentPlayer->isBankrupt()) {
        std::cout << currentPlayer->getName() << " is bankrupt and out of the game!\n";
        players.erase(players.begin() + currentPlayerIndex);
        if (currentPlayerIndex >= players.size()) {
            currentPlayerIndex = 0;
        }
    }
}

void Game::nextPlayer() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}
