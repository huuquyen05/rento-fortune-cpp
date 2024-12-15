#include "game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unordered_map>
#include "property.h"
#include "player.h"
#include "slot.h"

// Global map to map player names to their indices in the players vector
std::unordered_map<std::string, int> playerNameToIndex;

// Constructor for the Game class
Game::Game(int numPlayers) : currentPlayerIndex(0) {
    // Loop to create players with user-defined names
    for (int i = 0; i < numPlayers; ++i) {
        std::string playerName;
        std::cout << "Enter name for Player " << i + 1 << ": ";
        std::cin >> playerName;
        players.push_back(new Player(playerName, 500, 1));
        playerNameToIndex[playerName] = i;  // Map player name to index
    }

    // 初始化棋盘
    slots.resize(40);
    slots[0] = new GoSlot();
    Property* vineStreetProperty = new Property("Vine Street", 60, 1);
    slots[1] = new PropertySlot(vineStreetProperty);
    slots[2] = new CommunityChestSlot();
    Property* coventryStreetProperty = new Property("Coventry Street", 60, 1);
    slots[3] = new PropertySlot(coventryStreetProperty);
    slots[4] = new LuxuryTaxSlot();
    Property* maryleboneStationProperty = new Property("Marylebone Station", 200, 9);
    slots[5] = new RailwayStationSlot(maryleboneStationProperty);
    Property* leicesterSquareProperty = new Property("Leicester Square", 100, 2);
    slots[6] = new PropertySlot(leicesterSquareProperty);
    slots[7] = new ChanceSlot();
    Property* bowStreetProperty = new Property("Bow Street", 100, 2);
    slots[8] = new PropertySlot(bowStreetProperty);
    Property* whitechapelRoadProperty = new Property("Whitechapel Road", 120, 2);
    slots[9] = new PropertySlot(whitechapelRoadProperty);
    slots[10] = new JailSlot();
    Property* angelIslingtonProperty = new Property("The Angel, Islington", 140, 3);
    slots[11] = new PropertySlot(angelIslingtonProperty);
    Property* electricCompanyProperty = new Property("Electric Company", 150, 10);
    slots[12] = new UtilitySlot(electricCompanyProperty);
    Property* trafalgarSquareProperty = new Property("Trafalgar Square", 140, 3);
    slots[13] = new PropertySlot(trafalgarSquareProperty);
    Property* northumrlAvenueProperty = new Property("Northumrl'd Avenue", 160, 3);
    slots[14] = new PropertySlot(northumrlAvenueProperty);
    Property* fenchurchStationProperty = new Property("Fenchurch st.Station", 200, 9);
    slots[15] = new RailwayStationSlot(fenchurchStationProperty);
    Property* mBoroughStreetProperty = new Property("M'Borough Street", 180, 4);
    slots[16] = new PropertySlot(mBoroughStreetProperty);
    slots[17] = new CommunityChestSlot();
    Property* fleetStreetProperty = new Property("Fleet Street", 180, 4);
    slots[18] = new PropertySlot(fleetStreetProperty);
    Property* oldKentRoadProperty = new Property("Old Kent Road", 200, 4);
    slots[19] = new PropertySlot(oldKentRoadProperty);
    slots[20] = new ParkSlot();
    Property* whiteHallProperty = new Property("White Hall", 220, 5);
    slots[21] = new PropertySlot(whiteHallProperty);
    slots[22] = new ChanceSlot();
    Property* pentonvilleRoadProperty = new Property("Pentonville Road", 220, 5);
    slots[23] = new PropertySlot(pentonvilleRoadProperty);
    Property* pallMallProperty = new Property("Pall Mall", 240, 5);
    slots[24] = new PropertySlot(pallMallProperty);
    Property* kingsCrossStationProperty = new Property("Kings Cross Station", 200, 9);
    slots[25] = new RailwayStationSlot(kingsCrossStationProperty);
    Property* bondStreetProperty = new Property("Bond Street", 260, 6);
    slots[26] = new PropertySlot(bondStreetProperty);
    Property* strandProperty = new Property("Strand", 260, 6);
    slots[27] = new PropertySlot(strandProperty);
    Property* waterWorksProperty = new Property("Water Works", 150, 10);
    slots[28] = new UtilitySlot(waterWorksProperty);
    Property* regentStreetProperty = new Property("Regent Street", 280, 6);
    slots[29] = new PropertySlot(regentStreetProperty);
    slots[30] = new GoToJailSlot();
    Property* eustonRoadProperty = new Property("Euston Road", 300, 7);
    slots[31] = new PropertySlot(eustonRoadProperty);
    Property* piccadillyProperty = new Property("Piccadilly", 300, 7);
    slots[32] = new PropertySlot(piccadillyProperty);
    slots[33] = new CommunityChestSlot();
    Property* oxfordStreetProperty = new Property("Oxford Street", 320, 7);
    slots[34] = new PropertySlot(oxfordStreetProperty);
    Property* liverpoolStationProperty = new Property("Liverpool st.Station", 200, 9);
    slots[35] = new RailwayStationSlot(liverpoolStationProperty);
    slots[36] = new ChanceSlot();
    Property* parkLaneProperty = new Property("Park Lane", 350, 8);
    slots[37] = new PropertySlot(parkLaneProperty);
    slots[38] = new SuperTaxSlot();
    Property* mayfairProperty = new Property("Mayfair", 400, 8);
    slots[39] = new PropertySlot(mayfairProperty);
    // 可以继续添加更多格子...
}

Game::Game(std::string names[4]) : currentPlayerIndex(0) {
    int numPlayers = 4;
    // Loop to create players with user-defined names
    for (int i = 0; i < numPlayers; ++i) {
        std::string playerName = names[i];
        players.push_back(new Player(playerName, 10, 1));
        playerNameToIndex[playerName] = i;  // Map player name to index
    }
    // 初始化棋盘
    slots.resize(40);
    slots[0] = new GoSlot();
    Property* vineStreetProperty = new Property("Vine Street", 60, 1);
    slots[1] = new PropertySlot(vineStreetProperty);
    slots[2] = new CommunityChestSlot();
    Property* coventryStreetProperty = new Property("Coventry Street", 60, 1);
    slots[3] = new PropertySlot(coventryStreetProperty);
    slots[4] = new LuxuryTaxSlot();
    Property* maryleboneStationProperty = new Property("Marylebone Station", 200, 9);
    slots[5] = new RailwayStationSlot(maryleboneStationProperty);
    Property* leicesterSquareProperty = new Property("Leicester Square", 100, 2);
    slots[6] = new PropertySlot(leicesterSquareProperty);
    slots[7] = new ChanceSlot();
    Property* bowStreetProperty = new Property("Bow Street", 100, 2);
    slots[8] = new PropertySlot(bowStreetProperty);
    Property* whitechapelRoadProperty = new Property("Whitechapel Road", 120, 2);
    slots[9] = new PropertySlot(whitechapelRoadProperty);
    slots[10] = new JailSlot();
    Property* angelIslingtonProperty = new Property("The Angel, Islington", 140, 3);
    slots[11] = new PropertySlot(angelIslingtonProperty);
    Property* electricCompanyProperty = new Property("Electric Company", 150, 10);
    slots[12] = new UtilitySlot(electricCompanyProperty);
    Property* trafalgarSquareProperty = new Property("Trafalgar Square", 140, 3);
    slots[13] = new PropertySlot(trafalgarSquareProperty);
    Property* northumrlAvenueProperty = new Property("Northumrl'd Avenue", 160, 3);
    slots[14] = new PropertySlot(northumrlAvenueProperty);
    Property* fenchurchStationProperty = new Property("Fenchurch st.Station", 200, 9);
    slots[15] = new RailwayStationSlot(fenchurchStationProperty);
    Property* mBoroughStreetProperty = new Property("M'Borough Street", 180, 4);
    slots[16] = new PropertySlot(mBoroughStreetProperty);
    slots[17] = new CommunityChestSlot();
    Property* fleetStreetProperty = new Property("Fleet Street", 180, 4);
    slots[18] = new PropertySlot(fleetStreetProperty);
    Property* oldKentRoadProperty = new Property("Old Kent Road", 200, 4);
    slots[19] = new PropertySlot(oldKentRoadProperty);
    slots[20] = new ParkSlot();
    Property* whiteHallProperty = new Property("White Hall", 220, 5);
    slots[21] = new PropertySlot(whiteHallProperty);
    slots[22] = new ChanceSlot();
    Property* pentonvilleRoadProperty = new Property("Pentonville Road", 220, 5);
    slots[23] = new PropertySlot(pentonvilleRoadProperty);
    Property* pallMallProperty = new Property("Pall Mall", 240, 5);
    slots[24] = new PropertySlot(pallMallProperty);
    Property* kingsCrossStationProperty = new Property("Kings Cross Station", 200, 9);
    slots[25] = new RailwayStationSlot(kingsCrossStationProperty);
    Property* bondStreetProperty = new Property("Bond Street", 260, 6);
    slots[26] = new PropertySlot(bondStreetProperty);
    Property* strandProperty = new Property("Strand", 260, 6);
    slots[27] = new PropertySlot(strandProperty);
    Property* waterWorksProperty = new Property("Water Works", 150, 10);
    slots[28] = new UtilitySlot(waterWorksProperty);
    Property* regentStreetProperty = new Property("Regent Street", 280, 6);
    slots[29] = new PropertySlot(regentStreetProperty);
    slots[30] = new GoToJailSlot();
    Property* eustonRoadProperty = new Property("Euston Road", 300, 7);
    slots[31] = new PropertySlot(eustonRoadProperty);
    Property* piccadillyProperty = new Property("Piccadilly", 300, 7);
    slots[32] = new PropertySlot(piccadillyProperty);
    slots[33] = new CommunityChestSlot();
    Property* oxfordStreetProperty = new Property("Oxford Street", 320, 7);
    slots[34] = new PropertySlot(oxfordStreetProperty);
    Property* liverpoolStationProperty = new Property("Liverpool st.Station", 200, 9);
    slots[35] = new RailwayStationSlot(liverpoolStationProperty);
    slots[36] = new ChanceSlot();
    Property* parkLaneProperty = new Property("Park Lane", 350, 8);
    slots[37] = new PropertySlot(parkLaneProperty);
    slots[38] = new SuperTaxSlot();
    Property* mayfairProperty = new Property("Mayfair", 400, 8);
    slots[39] = new PropertySlot(mayfairProperty);
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

int Game::getCurPlayer(){
    return currentPlayerIndex;
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
std::pair<int, int> Game::rollDice() {
    int dice1 = rand() % 6 + 1;  // Random roll for the first die
    int dice2 = rand() % 6 + 1;  // Random roll for the second die
    std::cout << "Rolled: " << dice1 << " and " << dice2 << "\n";
    
    // If the player is not in jail, move them based on dice rolls
    if (!players[currentPlayerIndex]->isInJail()) {
        players[currentPlayerIndex]->move(dice1 + dice2);
        players[currentPlayerIndex]->setlaststep(dice1 + dice2);
        //std::cout<<players[currentPlayerIndex]->getPosition()<<std::endl;
    } else {
        // If the player is in jail, check if they rolled doubles to get out
        if (dice1 == dice2) {
            players[currentPlayerIndex]->getOutOfJail();
        }
    }
    //std::cout<<"enter"<<std::endl;
    return {dice1, dice2};
}

// Handle the current player's turn (land on a slot and trigger its event)
void Game::processTurn() {
    Player* currentPlayer = players[currentPlayerIndex];
    Slot* currentSlot = slots[currentPlayer->getPosition()];
    
    std::cout << currentPlayer->getName() << " rolled the dice and landed on " << currentSlot->getName() << "\n";
    
    // Trigger any events based on the slot
    currentSlot->landOn(currentPlayer, players);  // This could trigger actions like paying rent, drawing cards, etc.
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
