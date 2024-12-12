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

void Player::buyProperty(Property* property) {
    if (money >= property->getPrice()) {
        money -= property->getPrice();
        addProperty(property);
        property->setOwner(this);
        property->changePrice(0.5 * property->getPrice());
        std::cout << name << " bought " << property->getName() << "\n";
    } else {
        std::cout << name << " cannot afford " << property->getName() << "\n";
    }
}

void Player::upgradeProperty(Property* property) {
    if (money >= property->getPrice()) {
        money -= property->getPrice();
        property->upgrade();
        if (property->getLevel() == 5) {
            ++NumberOfHotels;
            --NumberOfHouses;
        }
        std::cout << name << " upgrade " << property->getName() << "\n";
    } else {
        std::cout << name << " cannot upgrade " << property->getName() << "\n";
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