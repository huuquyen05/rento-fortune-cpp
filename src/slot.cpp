#include "slot.h"
#include "property.h"
#include <iostream>

PropertySlot::PropertySlot(Property* p) : property(p) {
    name = property->getName();
}

void PropertySlot::landOn(Player& player) {
    if (property->getOwner() == nullptr) {
        // to be continued
        player.buyProperty(property);
    } else {
        property->payRent(player);
    }
}