#include <random>
#include <iostream>
#include "property.h"
#include "player.h"
using namespace std;

Property::Property(string name, int costList[], int rentList[]) {
    name = name;
    for(int i = 0; i < 5; ++i) {
        listOfUpgradeCost[i] = costList[i];
        listOfRent[i] = rentList[i];
    }
    owner = new Player();
    level = -1;
}

std::string Property::getName() {
    return name;
}

void Property::upgrade() {
    if(level == 4) {
        cerr << "Maxed, cannot be upgraded." << '\n';
        return;
    }
    if(owner -> getMoney() < listOfUpgradeCost[level + 1]) {
        cerr << "Not enought money." << '\n';
        return;
    }
    ++level;
    owner -> payMoney(listOfUpgradeCost[level]);
}

void Property::payRent(Player *player) {
    if(player -> getMoney() < listOfRent[level]) {
        player -> goBankruptcy();
        return;
    }
    player -> payMoney(listOfRent[level]);
    owner -> gainMoney(listOfRent[level]);
}