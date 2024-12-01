#ifndef CHANCE_H
#define CHANCE_H

#include <random>

class Chance {
private:
    int chancenum;
public:
    Chance();
    void advanceto();
    void collect();
    void pay();
}