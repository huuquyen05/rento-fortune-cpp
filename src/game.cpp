#include "game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unordered_map>
#include "property.h"

// Global map to map player names to their indices in the players vector
std::unordered_map<std::string, int> playerNameToIndex;

// Constructor for the Game class
Game::Game(int numPlayers) : currentPlayerIndex(0) {
    // Loop to create players with user-defined names
    for (int i = 0; i < numPlayers; ++i) {
        std::string playerName;
        std::cout << "Enter name for Player " << i + 1 << ": ";
        std::cin >> playerName;
        players.push_back(new Player(playerName));
        playerNameToIndex[playerName] = i;  // Map player name to index
    }

    // 初始化棋盘
    slots.resize(40);
    slots[0] = new ParkSlot();
    Property* vineStreetProperty = new Property("Vine Street", 60);
    slots[1] = new PropertySlot(vineStreetProperty);    
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
    slots[27] = new PropertySlot(new Property("Strand", 260));
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

// Method to get all players for other purposes (e.g., Chance cards)
std::vector<Player*> Game::getAllPlayers() {
    return players;
}

// Method to get the number of players in the game
int Game::getNumOfPlayers() {
    return players.size();
}

// Initialize game settings, like shuffling cards or other initializations
void Game::initGame() {
    srand(time(0));  // Random seed for dice rolls
    // Additional game setup (e.g., shuffling cards) can be added here
}

// Start a new turn for the current player
void Game::startTurn() {
    Player* currentPlayer = players[currentPlayerIndex];
    std::cout << currentPlayer->getName() << "'s turn\n";
    rollDice();  // Player rolls the dice
    processTurn();  // Process the turn (move, interact with slots, etc.)
}

// Roll two dice and move the player accordingly
void Game::rollDice() {
    int dice1 = rand() % 6 + 1;  // Random roll for the first die
    int dice2 = rand() % 6 + 1;  // Random roll for the second die
    std::cout << "Rolled: " << dice1 << " and " << dice2 << "\n";
    
    // If the player is not in jail, move them based on dice rolls
    if (!players[currentPlayerIndex]->isInJail()) {
        players[currentPlayerIndex]->move(dice1 + dice2);
    } else {
        // If the player is in jail, check if they rolled doubles to get out
        if (dice1 == dice2) {
            players[currentPlayerIndex]->getOutOfJail();
        }
    }
}

// Handle the current player's turn (land on a slot and trigger its event)
void Game::processTurn() {
    Player* currentPlayer = players[currentPlayerIndex];
    Slot* currentSlot = board[currentPlayer->getPosition()];
    
    std::cout << currentPlayer->getName() << " rolled the dice and landed on " << currentSlot->getName() << "\n";
    
    // Trigger any events based on the slot
    currentSlot->landOn(*currentPlayer, players);  // This could trigger actions like paying rent, drawing cards, etc.
    // Check if the player is bankrupt
    checkBankruptcy();
    // Move to the next player after the turn is finished
    nextPlayer();
}

// Check if the current player has gone bankrupt
void Game::checkBankruptcy() {
    Player* currentPlayer = players[currentPlayerIndex];
    if(currentPlayer->getMoney() < 0){
        while(currentPlayer->getMoney() < 0 && currentPlayer->hasProperty()){
            currentPlayer->mortgage();
        }
        if(currentPlayer->getMoney() < 0){
            currentPlayer->goBankrupt();
        }
    }
}

void Game::nextPlayer() {
    do {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    } while (players[currentPlayerIndex]->isBankrupt());  // Skip bankrupt players
}
