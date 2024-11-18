#ifndef dice_h
#define dice_h

#include <random>

class Dice {
private:
    int d1, d2;
public:
    Dice();
    void rollValue();
    bool isDouble();
    int getD1();
    int getD2();
};

#endif