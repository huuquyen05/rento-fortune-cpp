# Rento Fortune cpp

## Core classes (add more description)
1. Dice
    - Field:
        - int d1
        - int d2 
    - Method
        - void rollValue()
        - bool isDouble()
        - int getD1() 
        - int getD2()
2. Player
    - Field
        - string name
        - int playerIndex
        - int money
        - vector\<Property*> properties
        - bool inJail
        - int outOfJailFree
        - bool bankruptcy
        - int position
        - int colourOfToken
    - Method
        - void init()
        - string getName()
        - int getPlayerIndex()
        - int getMoney()
        - void gainMoney(int amount)
        - void payMoney(int amount)
        - int getNumberOf(int kindOfProperty)
        - void addProperty(int indexOfSlot)
        - void identifyPropertyType(Property* property)
        - vector\<int> getProperty()
        - bool checkInJail()
        - int getOutOfJailFree()
        - void putInJail()
        - void outOfJail()
        - bool checkBankruptcy()
        - void goBankruptcy()
        - int checkLocation()
        - void changeLocation(int stepToMove)
        - int getColourOfToken()
3. Slot
    - Superclass
        - Slot
    - Subclass
        - PropertySlot
        - ParkSlot
        - SuperTaxSlot
        - LuxuryTaxSlot
        - ChanceSlot
        - GoToJailSlot
        - RailwayStationSlot
        - CommunityChestSlot
        - UtilitySlot
    - Method
        - void init()
        - void landOn()
        - string getName()
4. Property
    - Normal Property
        - Field
            - string name
            - vector\<int> listOfUpgradeCost
            - vector\<int> listOfRent
            - Player *owner
            - int level
            - int type
        - Method
            - void upgrade()
            - int getType()
            - void getName()
            - Player* getOwner()
            - void buyLand(Player *player)
            - void payRent(Player *player)
    - Utility
        - Field
            - string name
            - Player *owner
            - int baseRentMultiplier;
            - int price
        - Method
            - int getType()
            - void getName()
            - Player* getOwner()
            - void buyLand(Player *player)
            - void payRent(Player *player)
    - Railroad
        - Field
            - string name
            - Player *owner
            - int baseRent;
            - int price
        - Method
            - int getType()
            - void getName()
            - Player* getOwner()
            - void buyLand(Player *player)
            - void payRent(Player *player)


5. game
    - Method
        - init()


## Basic game flow
1. init the players
2. game recursion
    - turn start 
    - check if bankruptcy
    - check if in jail
    - throw a dice
    - move
    - slot function
    - check if in jail
    - check if bankruptcy
    - mortage
    - trade
    - turn over

## Detailed Implementation
- The index is from 1 to 40, start from the starting point