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
