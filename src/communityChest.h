#ifndef COMMUNITY_H
#define COMMUNITY_H

#include <random>

class CommunityChest {
private:
    int chestnum;
public:
    CommunityChest();
    void advanceto();
    void collect();
    void pay();
}