#ifndef slot_h
#define slot_h

class Slot{
public:
    void init();
    void visitSlot(int NumberOfSlot);
    void visitGo();
    void visitSentToJail();
    void visitProperty();
    void visitCommunityChest();
    void visitChance();
    void visitFreeParking();
    void visitIncomeTax();
    void visitSuperTax();
};

#endif