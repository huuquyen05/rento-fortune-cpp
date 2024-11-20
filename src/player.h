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
    Player(string name, int colourOfToken);
    std::string getName();
    int getMoney();
    void gainMoney(int amount);
    void payMoney(int amount);
    int getNumberOf(int kindOfProperty);
    void addProperty(int indexOfSlot);
    bool checkInJail();
    void putInJail();
    void outOfJail();
    bool checkBankruptcy();
    void goBankruptcy();
    int checkLocation();
    void changeLocation(int stepToMove);
    int getColourOfToken();
};

#endif