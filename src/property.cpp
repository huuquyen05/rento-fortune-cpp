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
    owner = NULL;
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
    cout << "Do you want to upgrade this property for $" << listOfUpgradeCost[level + 1] << "?\n";
    cout << "The new rent fee will be $" << listOfRent[level + 1] << '\n';
    cout << "Enter 0 for no, 1 for yes\n";
    int x; cin >> x;
    if(x == 1) {
        ++level;
        owner -> payMoney(listOfUpgradeCost[level]);
    }
}

void Property::buyLand(Player *player) {
    if(owner != NULL) {
        cerr << "Already owned\n";
        return;
    }
    if(player -> getMoney() < listOfUpgradeCost[0]) {
        cerr << "Not enough money\n";
        return;
    }
    cout << "Do you want to buy this property for $" << listOfUpgradeCost[0] << "?\n";
    cout << "The new rent fee will be $" << listOfRent[0] << '\n';
    cout << "Enter 0 for no, 1 for yes\n";
    int x; cin >> x;
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
