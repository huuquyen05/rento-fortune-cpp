#include "player.h"
#include <iostream>
std::vector<Player*> players;

Player::Player(std::string name, int initialMoney, int tokenColor, int pI)
    : name(name), money(initialMoney), inJail(false), outJailcard(0), bankrupt(false), position(0), colourOfToken(tokenColor), playerIndex(pI), NumberOfHouses(0), NumberOfHotels(0) {}

std::string Player::getName() const {
    return name;
}

int Player::getMoney() const {
    return money;
}

int Player::getPosition() const {
    return position;
}

int Player::getColourOfToken() const {
    return colourOfToken;
}

void Player::updateMoney(int amount) {
    money += amount;
}

int Player::getPlayerIndex() const {
    return playerIndex;
}

int Player::getNumberOfPlayers() const {
    return NumberOfPlayers;
}

int Player::getNumberOfHouses() const {
    return NumberOfHouses;
}

int Player::getNumberOfHotels() const {
    return NumberOfHotels;
}

bool Player::checkoutJailcard() const {
    if (outJailcard < 1) {
        return false;
    }else {
        return true;
    }
}

void Player::setlaststep(int steps){
    laststep = steps;
}

void Player::move(int steps) {
    if (position + steps > 39){
        money += 200;
    }
    position = (position + steps + 40) % 40;  // 40格棋盘，循环走
}

void Player::moveto(int destination) {
    if (destination < position) {
        money += 200;
    }
    position = destination;
}
int Player::hasProperty(){
    return properties.size() > 0;
}
void Player::buyProperty(Property* property) {
    if (money >= property->getPrice()) {
        std::cout << name << ", do you want to buy " << property->getName() << " for $" << property->getPrice() << "? (yes/no): ";
        std::string choice;
        std::cin >> choice;

        if (choice == "yes") {
            // Proceed with the purchase
            money -= property->getPrice();  // Deduct the price
            addProperty(property);           // Add the property to player's list
            property->setOwner(this);        // Set the player as the owner of the property
            property->changePrice(0.5 * property->getPrice());
            std::cout << name << " bought " << property->getName() << "\n";
        } else {
            std::cout << name << " decided not to buy " << property->getName() << "\n";
        }
    } else {
        std::cout << name << " cannot afford " << property->getName() << "\n";
    }
}

int Player::getlaststep(){
    return laststep;
}

void Player::upgradeProperty(Property* property) {
    if (property->getLevel() < 5){
        if (money >= property->getPrice()) {
            std::cout << name << ", do you want to upgrade " << property->getName() << " for $" << property->getPrice() << "? (yes/no): ";
            std::string choice;
            std::cin >> choice;

            if (choice == "yes") {
                money -= property->getPrice();
                property->upgrade();
                if (property->getLevel() == 5) {
                    ++NumberOfHotels;
                    --NumberOfHouses;
                }
                std::cout << name << " upgrade " << property->getName() << "\n";
            }else {
                std::cout << name << " decided not to upgrade " << property->getName() << "\n";
            }
        } else {
            std::cout << name << " cannot upgrade " << property->getName() << "\n";
        }
    }else {
        std::cout << property->getName() << "has been full level!" << "\n";
    }
}

bool Player::isInJail() const {
    return inJail;
}

void Player::goToJail() {
    inJail = true;
    position = 10;
}

void Player::getOutOfJail() {
    inJail = false;
    position = 10;
}

void Player::haveoutJailcard() {
    ++outJailcard;
}

void Player::useoutJailcard() {
    --outJailcard;
}

bool Player::isBankrupt() const {
    return bankrupt;
}

void Player::goBankrupt() {
    bankrupt = true;
}

void Player::addProperty(Property* property) {
    properties.push_back(property);
}

void Player::mortgage() {
    if (properties.empty()) {
        std::cout << name << " has no properties to mortgage.\n";
        return;
    }

    std::cout << "Choose a property to mortgage (0-" << properties.size() - 1 << "):\n";
    for (int i = 0; i < properties.size(); ++i) {
        std::cout << i << ": " << properties[i]->getName() << " (Value: $" << properties[i]->getPrice() << ")\n";
    }

    int choice;
    std::cin >> choice;

    if (choice >= 0 && choice < properties.size()) {
        Property* propertyToMortgage = properties[choice];
        int mortgageValue = propertyToMortgage->getPrice() / 2;  // 50% of the property value

        money += mortgageValue;
        std::cout << name << " mortgaged " << propertyToMortgage->getName() 
                  << " for $" << mortgageValue << ".\n";
        
        propertyToMortgage->setOwner(nullptr);
        properties.erase(properties.begin() + choice);

        if (money >= 0) {
            std::cout << name << " now has $" << money << ".\n";
        }
    } else {
        std::cout << "Invalid choice. No property mortgaged.\n";
    }
}
