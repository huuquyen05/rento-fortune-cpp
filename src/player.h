#ifndef player_h
#define player_h

#include <string>
#include <vector>

class Player {
private:
    std::string name;
    int money;
    std::vector <int> properties;
    bool inJail;
    bool bankruptcy;
    int location;
    int colourOfToken;
public:
    Player(); // default constructor
    std::string getName();
    int getMoney();
    void gainMoney(int amount);
    void payMoney(int amount);
    int getNumberOf(std::string kindOfProperty); // kindOfProperty is the color of it
    void addProperty(int fuckkk);
};

#endif