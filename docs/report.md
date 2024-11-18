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
    - Field
        - bool isStartingPoint
        - bool isJail
        - bool isSentToJail
        - bool isProperty
        - bool isTrainStation
        - bool isCommunityChest
        - bool isChance
        - bool isFreeParking
        - bool isElectricCompany
        - bool isIncomeTax
        - bool isSuperTax
        - bool isWaterWorks 
    - Method
        - void init
        - void visitSlot(int NumberOfSlot)
        - int getNumOfToken()
        - 
4. Property
    - Field
        -hey


## Basic game flow

## Detailed Implementation