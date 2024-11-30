#include <random>
#include <iostream>
#include "property.h"
#include "player.h"

int type;
int listOfUpgradeCost[5];
int listOfRent[5];
int level;
Player* owner;

Property::Property(std::string name, int costList[], int rentList[], int Type) {
    name = name;
    for(int i = 0; i < 5; ++i) {
        listOfUpgradeCost[i] = costList[i];
        listOfRent[i] = rentList[i];
    }
    owner = NULL;
    type = Type;
    level = -1;
}

std::string Property::getName() {
    return name;
}

int Property::getType() {
    return type;
}
/*
void Property::upgrade() {
    if(level == 4) {
        std::cerr << "Maxed, cannot be upgraded." << '\n';
        return;
    }
    if(owner -> getMoney() < listOfUpgradeCost[level + 1]) {
        std::cerr << "Not enought money." << '\n';
        return;
    }
    std::cout << "Do you want to upgrade this property for $" << listOfUpgradeCost[level + 1] << "?\n";
    std::cout << "The new rent fee will be $" << listOfRent[level + 1] << '\n';
    std::cout << "Enter 0 for no, 1 for yes\n";
    int x; std::cin >> x;
    if(x == 1) {
        ++level;
        owner -> payMoney(listOfUpgradeCost[level]);
    }
}
*/
void Property::buyLand(Player *player) {
    if(owner != NULL) {
        std::cerr << "Already owned\n";
        return;
    }
    if(player -> getMoney() < listOfUpgradeCost[0]) {
        std::cerr << "Not enough money\n";
        return;
    }
    std::cout << "Do you want to buy this property for $" << listOfUpgradeCost[0] << "?\n";
    std::cout << "The new rent fee will be $" << listOfRent[0] << '\n';
    std::cout << "Enter 0 for no, 1 for yes\n";
    int x; std::cin >> x;
    if(x == 1) {
        ++level;
        owner = player;
        owner -> payMoney(listOfUpgradeCost[0]);
    }
}

void Property::payRent(Player *player) {
    if(player -> getMoney() < listOfRent[level]) {
        player -> goBankruptcy();
        return;
    }
    player -> payMoney(listOfRent[level]);
    owner -> gainMoney(listOfRent[level]);
}
