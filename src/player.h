#ifndef player_h
#define player_h

#include <string>

class Player {
private:
    string name;
    int money;
    vector <int> properties;
    bool inJail;
    bool bankruptcy;
    int location;
    int colourOfToken;
public:
    Player(); // default constructor
    string getName();
    int getMoney();
    void gainMoney(int amount);
    void payMoney(int amount);
    int getNumberOf(string kindOfProperty); //
}

#endif