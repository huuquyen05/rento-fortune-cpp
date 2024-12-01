#ifndef COMMUNITYCHEST_H
#define COMMUNITYCHEST_H

#include <bits/stdc++.h>
#include "player.h"

class CommunityChest{
    private:
    std::string type;
    int amount;
    std::string sentence;
    int steps;
    int location;
    public:
    CommunityChest(std::string type,int amount,std::string sentence,int steps,int location);
    void trigger(Player* player);
};

#endif