#include <random>
#include "dice.h"
using namespace std;

Dice :: Dice() {
    d1 = d2 = 0;
}

void Dice :: rollValue() {
    d1 = rand() % 6 + 1;
    d2 = rand() % 6 + 1;
}

bool Dice :: isDouble() {
    return d1 == d2;
}

int Dice :: getD1() {
    return d1;
}

int Dice :: getD2() {
    return d2;
}