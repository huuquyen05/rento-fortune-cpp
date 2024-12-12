#include "game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

Game::Game(int numPlayers) : currentPlayerIndex(0) {
    for (int i = 0; i < numPlayers; ++i) {
        players.push_back(new Player("Player " + std::to_string(i + 1)));
    }

    // 初始化棋盘
    slots.resize(40);
    slots[0] = new ParkSlot();
    slots[1] = new PropertySlot(new Property("Vine Street", 60));
    slots[2] = new CommunityChestSlot();
    slots[3] = new PropertySlot(new Property("Coventry Street", 60));
    slots[4] = new LuxuryTaxSlot();
    slots[5] = new RailwayStationSlot(new Property("Marylebone Station", 200));
    slots[6] = new PropertySlot(new Property("Leicester Square", 100));
    slots[7] = new ChanceSlot();
    slots[8] = new PropertySlot(new Property("Bow Street", 100));
    slots[9] = new PropertySlot(new Property("Whitechapel Road", 120));
    slots[10] = new GoToJailSlot();
    slots[11] = new PropertySlot(new Property("The Angel, Islington", 140));
    slots[12] = new UtilitySlot(new Property("Electric Company", 150));
    slots[13] = new PropertySlot(new Property("Trafalgar Square", 140));
    slots[14] = new PropertySlot(new Property("Northumrl'd Avenue", 160));
    slots[15] = new RailwayStationSlot(new Property("Fenchurch st.Station", 200));
    slots[16] = new PropertySlot(new Property("M'Borough Street", 180));
    slots[17] = new CommunityChestSlot();
    slots[18] = new PropertySlot(new Property("Fleet Street", 180));
    slots[19] = new PropertySlot(new Property("Old Kent Road", 200));
    slots[20] = new ParkSlot();
    slots[21] = new PropertySlot(new Property("White Hall", 220));
    slots[22] = new ChanceSlot();
    slots[23] = new PropertySlot(new Property("Pentonville Road", 220));
    slots[24] = new PropertySlot(new Property("Pall Mall", 240));
    slots[25] = new RailwayStationSlot(new Property("Kings Cross Station", 200));
    slots[26] = new PropertySlot(new Property("Bond Street", 260));
    slots[27] = new PropertySlot(new Property("Strand"), 260);
    slots[28] = new UtilitySlot(new Property("Water Works", 150));
    slots[29] = new PropertySlot(new Property("Regent Street", 280));
    slots[30] = new GoToJailSlot();
    slots[31] = new PropertySlot(new Property("Euston Road", 300));
    slots[32] = new PropertySlot(new Property("Piccadilly", 300));
    slots[33] = new CommunityChestSlot();
    slots[34] = new PropertySlot(new Property("Oxford Street", 320));
    slots[35] = new RailwayStationSlot(new Property("Liverpool st.Station", 200));
    slots[36] = new ChanceSlot();
    slots[37] = new PropertySlot(new Property("Park Lane", 350));
    slots[38] = new SuperTaxSlot();
    slots[39] = new PropertySlot(new Property("Mayfair", 400));
    // 可以继续添加更多格子...
}

std::vector<Player*> getAllPlayers() {
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
    // trade
    processTurn();
}

void Game::rollDice() {
    int dice1 = rand() % 6 + 1;  // 随机掷骰子
    int dice2 = rand() % 6 + 1;
    std::cout << "Rolled: " << dice1 << " and " << dice2 << "\n";
    if (players[currentPlayerIndex]->isInJail() == false) {
        players[currentPlayerIndex]->move(dice1 + dice2);
    }else {
        if (dice1 == dice2)  players[currentPlayerIndex]->getOutOfJail() ; //在监狱里的判断
    }
}

void Game::processTurn() {
    Player* currentPlayer = players[currentPlayerIndex];
    Slot* currentSlot = board[currentPlayer->getPosition()];
    std::cout << currentPlayer->getName() << " landed on " << currentSlot->getName() << "\n";
    currentSlot->landOn(*currentPlayer, players);
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
