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
        - vector\<int> properties
        - bool inJail
        - int outOfJailFree
        - bool bankruptcy
        - int location
        - int colourOfToken
    - Method
        - void init()
        - string getName()
        - int getPlayerIndex()
        - int getMoney()
        - void gainMoney(int amount)
        - void payMoney(int amount)
        - int getNumberOf(string kindOfProperty)
        - void addProperty(int indexOfSlot)
        - vector\<int> getProperty()
        - bool checkInJail()
        - bool getOutOfJailFree()
        - void putInJail()
        - void outOfJail()
        - bool checkBankruptcy()
        - void goBankruptcy()
        - int checkLocation()
        - void changeLocation(int stepToMove)
        - int getColourOfToken()
3. Slot
    - Method
        - void init()
        - void visitSlot(int NumberOfSlot)()
        - void visitGo()
        - void visitSentToJail()
        - void visitProperty()
        - void visitRailroad()
        - void visitCommunityChest()
        - void visitChance()
        - void visitFreeParking()
        - void visitElectricCompany()
        - void visitIncomeTax()
        - void visitSuperTax()
        - void visitWaterWorks()
4. Property
    - Field
        - string name
        - vector\<int> listOfUpgradeCost
        - vector\<int> listOfRent
        - int Owner
        - int level
    - Method
        - void getName()
        - void upgrade()
        - void buyLand(Player *player)
        - void payRent(Player *player)
        - void getRent(Player *player)
5. Chance(TBD)
    - Field
    - Method
        - void trigger(Player *player)
        - void advanceToGo(Player *player)
        - void advancetoTrafalgarSquare(Player *player)
        - void advanceToPallMall(Player *player)
        - void advaceToNearestUtility(Player *player)
        - void advanceToNearestRailroad(Player *player)
        - void get50(Player *player)
        - void getOutOfJailFree(Player *player)
        - void goBackThreeSteps(Player *player)
        - void goToJail(Player *player)
        - void repairAllProperties(Player *player)
        - void advanceToKingsCrossStation(Player *player)
        - payPoorTaxOf15(Player *player)
        - advanceToMayfair(Player *player)
        - void payEach50(Player *player)
        - void get150(Player *player)
6. CommunityChest(TBD)
7. Game
    - Method
        - 



## Basic game flow

## Detailed Implementation
- The index is from 1 to 40, start from the starting point