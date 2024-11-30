#include "player.h"
#include <iostream>

Player::Player(std::string name, int initialMoney, int tokenColor)
    : name(name), money(initialMoney), inJail(false), bankrupt(false), position(0), colourOfToken(tokenColor) {}

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

void Player::move(int steps) {
    position = (position + steps) % 40;  // 40格棋盘，循环走
}

void Player::buyProperty(Property* property) {
    if (money >= property->getPrice()) {
        money -= property->getPrice();
        addProperty(property);
        property->setOwner(this);
        std::cout << name << " bought " << property->getName() << "\n";
    } else {
        std::cout << name << " cannot afford " << property->getName() << "\n";
    }
}

bool Player::isInJail() const {
    return inJail;
}

void Player::goToJail() {
    inJail = true;
}

void Player::getOutOfJail() {
    inJail = false;
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
