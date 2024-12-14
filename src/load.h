#ifndef LOAD_H
#define LOAD_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "game.h"
#include "property.h"
#include "slot.h"
#include <string>
#include <sstream>
#include <unistd.h>
#include <filesystem>
#include <fstream>

class Load{
private:
struct playerRecord {
    std::string player;
    int position;
    bool inJail;
    int outOFJailCard;
    int money;
    bool bankruptcy;
    std::string inTurn;
};
struct propertyRecord{
    int num;
    int level;
    int owner;
};
struct otherRecord{
    int owner;
};
public:
    void loadPlayer();
    void loadProperty();
    void loadOther();
    void loadALL();
};

#endif