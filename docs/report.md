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
        - int money
        - vector\<int> properties
        - bool inJail
        - bool bankruptcy
        - int location
        - int colourOfToken
    - Method
        - void init()
        - string getName()
        - int getMoney()
        - void gainMoney(int amount)
        - void payMoney(int amount)
        - int getNumberOf(string kindOfProperty)
        - void addProperty(int indexOfSlot)
        - bool checkInJail()
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
        - vector\<int> listOfUpgradeCost
        - vector\<int> listOfRent
        - int landPrice
        - int Owner
        - int level
    - Method
        - void init()
        - void upgrade()
        - void buyLand()
        - void payRent(string player,int level)
        - void getRent(string player,int level)
5. Chance(TBD)
    - Field
    - Method
        - void trigger()
        - void advanceToGo()
        - void 
6. CommunityChest(TBD)
7. Game
    - 



## Basic game flow

## Detailed Implementation
- The index is from 1 to 40, start from the starting point