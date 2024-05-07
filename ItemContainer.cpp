#include "ItemContainer.hpp"

/*Item containers
*    - Split into backpack, worn, treasure chest
* Backpack:
*    - Contain a limiting amout of item (maybe no need to implement yet)
*    - Can receive any new item and taken out
* Worn:
*    - Can only carry 1 of each type (may use struct, but it should be under item so probably no)
*    - When add, need to check/replace (wonder if i need to take in a backpack and check it there?)
* Treasure chest:
*    - Carry multiple item
*    - Can get from similar to back pack
*    - Acutally not even sure what's the difference (maybe just names)
*/

ItemContainer::ItemContainer() :items() {};
bool ItemContainer::addItem(Item* item) {
    this->items.push_back(item);
    return true;
}
bool ItemContainer::removeItem(Item* item) { //true if removed, false if not found
    for (int i = 0; i < this->items.size(); i++) {
        if (item == this->items.at(i)) {
            this->items.erase(items.begin()+i); // It needs to know where to start (relative position?)
            return true;
        }
    }
    return false;
}

bool ItemContainer::removeItem(string name) { // Similar to above but uses name instead (might have problem like same name)
    for (int i = 0; i < this->items.size(); i++) {
        if (name == this->items.at(i)->getName()) {
            this->items.erase(items.begin() + i);
            return true;
        }
    }
    return false;
}
Item* ItemContainer::takeItem(string name) {
    for (int i = 0; i < this->items.size(); i++) {
        if (name == this->items.at(i)->getName()) {
            Item* temp = items.at(i); // This create a copy of the item and return the
            this->items.erase(items.begin() + i);
            return temp;
        }
    }
    return nullptr;
}
std::vector<Item*> ItemContainer::getItems() const{
    return this->items;
}

void ItemContainer::displayItems() const{
    for (int i = 0; i < this->items.size(); i++) {
        std::cout<<i+1<<":";
        this->items.at(i)->displayItem();
        }
}

Backpack::Backpack() {
    this->size = 20; //Default to 20
}
Backpack::Backpack(int size) {
    this->size = size;
}
bool Backpack::addItem(std::shared_ptr<Item> item) { // Accept std::shared_ptr<Item>
    if (this->size > this->items.size()) {
        this->items.push_back(item.get()); // No need to change this line; it works with std::shared_ptr
        return true;
    }
    return false;
}
bool Backpack::removeItem(Item* item) {
    for (int i = 0; i < this->items.size(); i++) {
        if (item == this->items.at(i)) {
            this->items.erase(items.begin() + i);
            return true;
        }
    }
    return false;
}
bool Backpack::removeItem(string name) {
    for (int i = 0; i < this->items.size(); i++) {
        if (name == this->items.at(i)->getName()) {
            this->items.erase(items.begin() + i);
            return true;
        }
    }
    return false;
}
int Backpack::getSize() const {
    return size;
}
Item* Backpack::getItemByName(const string& name) const {
    for (auto& item : items) {
        if (item->getName() == name) {
            return item;
        }
    }
    return nullptr;
}

Item* Backpack::takeItem(string name) {
    for (int i = 0; i < this->items.size(); i++) {
        if (name == this->items.at(i)->getName()) {
            Item* temp = items.at(i); // This create a copy of the item and return the
            this->items.erase(items.begin() + i);
            return temp;
        }
    }
    return nullptr;
};
WornItems::WornItems(){
    for (int i = 0; i < sizeof(this->equipped)/sizeof(this->equipped[0]); ++i) {
        this->equipped[i] = false; //Initially all false
    }
}

bool WornItems::addItem(Item* item) {
    if (checkIfEquipped(item)) {
        return false;
    }
    else {
        // Check the equipped (also if the item is right class before adding)
        if (const Helmet* helmet = dynamic_cast<const Helmet*>(item)) {
            this->items.push_back(item);
            this->equipped[0] = true;
            return true;
        }
        else if (const Armor* armor = dynamic_cast<const Armor*>(item)) {
            this->items.push_back(item);
            this->equipped[1] = true;
            return true;
        }
        else if (const Shield* shield = dynamic_cast<const Shield*>(item)) {
            this->items.push_back(item);
            this->equipped[2] = true;
            return true;
        }
        else if (const Ring* ring = dynamic_cast<const Ring*>(item)) {
            this->items.push_back(item);
            this->equipped[3] = true;
            return true;
        }
        else if (const Belt* belt = dynamic_cast<const Belt*>(item)) {
            this->items.push_back(item);
            this->equipped[4] = true;
            return true;
        }
        else if (const Boots* boots = dynamic_cast<const Boots*>(item)) {
            this->items.push_back(item);
            this->equipped[5] = true;
            return true;
        }
        else if (const Weapon* weapon = dynamic_cast<const Weapon*>(item)) {
            this->items.push_back(item);
            this->equipped[6] = true;
            return true;
        }
        return false;
    }
};
bool WornItems::removeItem(Item* item) {
    bool removed = false;

    // Iterate through the items to find the item to remove
    for (auto it = items.begin(); it != items.end(); ) {
        if (*it == item) {
            it = items.erase(it); // Remove the item and get the next iterator
            removed = true;
            // Do not break here if you want to ensure all instances of the item are removed
        }
        else {
            ++it; // Move to the next item
        }
    }

    // Update the equipped status based on the type of the item removed
    if (removed) {
        if (dynamic_cast<Helmet*>(item)) {
            equipped[0] = false;
        }
        else if (dynamic_cast<Armor*>(item)) {
            equipped[1] = false;
        }
        else if (dynamic_cast<Shield*>(item)) {
            equipped[2] = false;
        }
        else if (dynamic_cast<Ring*>(item)) {
            equipped[3] = false;
        }
        else if (dynamic_cast<Belt*>(item)) {
            equipped[4] = false;
        }
        else if (dynamic_cast<Boots*>(item)) {
            equipped[5] = false;
        }
        else if (dynamic_cast<Weapon*>(item)) {
            equipped[6] = false;
        }
    }

    return removed;
}
    
bool WornItems::removeItem(string name) { //Not as accurate as the one above but works
    bool removed = false;
    Item* temp = nullptr;
    for (int i = 0; i < this->items.size(); i++) {
        if ((name == this->items.at(i)->getName())
            && !removed) { // In case there's 2 item
            temp = this->items.at(i);
            this->items.erase(items.begin() + i);
            removed = true;
        }
    }
    // Uncheck the equipped
    if (const Helmet* helmet = dynamic_cast<const Helmet*>(temp)) {
        this->equipped[0] = false;
    }
    else if (const Armor* armor = dynamic_cast<const Armor*>(temp)) {
        this->equipped[1] = false;
    }
    else if (const Shield* shield = dynamic_cast<const Shield*>(temp)) {
        this->equipped[2] = false;
    }
    else if (const Ring* ring = dynamic_cast<const Ring*>(temp)) {
        this->equipped[3] = false;
    }
    else if (const Belt* belt = dynamic_cast<const Belt*>(temp)) {
        this->equipped[4] = false;
    }
    else if (const Boots* boots = dynamic_cast<const Boots*>(temp)) {
        this->equipped[5] = false;
    }
    else if (const Weapon* weapon = dynamic_cast<const Weapon*>(temp)) {
        this->equipped[6] = false;
    }
    return removed;
};
Item* WornItems::takeItem(string name) {
    Item* temp = nullptr;
    for (int i = 0; i < this->items.size(); i++) {
        if (name == this->items.at(i)->getName()) {
            temp = items.at(i); // This get a copy of the pointer
            this->items.erase(items.begin() + i); // Remove the item
        }
    }
    // Uncheck the equipped
    if (const Helmet* helmet = dynamic_cast<const Helmet*>(temp)) {
        this->equipped[0] = false;
    }
    else if (const Armor* armor = dynamic_cast<const Armor*>(temp)) {
        this->equipped[1] = false;
    }
    else if (const Shield* shield = dynamic_cast<const Shield*>(temp)) {
        this->equipped[2] = false;
    }
    else if (const Ring* ring = dynamic_cast<const Ring*>(temp)) {
        this->equipped[3] = false;
    }
    else if (const Belt* belt = dynamic_cast<const Belt*>(temp)) {
        this->equipped[4] = false;
    }
    else if (const Boots* boots = dynamic_cast<const Boots*>(temp)) {
        this->equipped[5] = false;
    }
    else if (const Weapon* weapon = dynamic_cast<const Weapon*>(temp)) {
        this->equipped[6] = false;
    }
    return temp;
};
bool WornItems::checkIfEquipped(Item* item) const { //This only check if that specific item slot is occupied
    // Use dynamic casting to check which class
    // Then check teh equipments to see if equipped
    if (const Helmet* helmet = dynamic_cast<const Helmet*>(item)) {
        return this->equipped[0];
    }
    else if (const Armor* armor = dynamic_cast<const Armor*>(item)) {
        return this->equipped[1];
    }
    else if (const Shield* shield = dynamic_cast<const Shield*>(item)) {
        return this->equipped[2];
    }
    else if (const Ring* ring = dynamic_cast<const Ring*>(item)) {
        return this->equipped[3];
    }
    else if (const Belt* belt = dynamic_cast<const Belt*>(item)) {
        return this->equipped[4];
    }
    else if (const Boots* boots = dynamic_cast<const Boots*>(item)) {
        return this->equipped[5];
    }
    else if (const Weapon* weapon = dynamic_cast<const Weapon*>(item)) {
        return this->equipped[6];
    }
    else {
        std::cout << "Unknown Item type.\n";
        return false;
    }
}
TreasureChest::TreasureChest() {
    Helmet* helmet1 = new Helmet("Baseball Helmet", intelligence, 2);
    Helmet* helmet2 = new Helmet("Construction Helmet", intelligence, 4);
    Armor* armor1 = new Armor("Mesh Armor", armorClass, 2);
    Shield* shield1 = new Shield("Steel Plate", armorClass, 3);
    Ring* ring1 = new Ring("The Cursed King's Ring", charisma, 4);
    Belt* belt1 = new Belt("Heavyweight World's Champion Belt", strength, 5);
    Boots* boots1 = new Boots("J", dexterity, 5);
    Weapon* weapon1 = new Weapon("Wooden spoon", attackBonus, 1);
    // Add each item pointer to the vector
       items.push_back(helmet1);
       items.push_back(helmet2);
    items.push_back(armor1);
    items.push_back(shield1);
    items.push_back(ring1);
    items.push_back(belt1);
    items.push_back(boots1);
    items.push_back(weapon1);
    
    
};

Item* TreasureChest::openChest(){
    if (items.empty()) {
        // Handle the case where items is empty
        return nullptr; // or throw an exception, depending on your design
    }
    srand(static_cast<unsigned int>(time(nullptr)));
       int randomIndex = rand() % items.size();

        //items[randomIndex]->displayItem();
       return  items[randomIndex];
    
}
bool TreasureChest::addItem(Item* item) {
    this->items.push_back(item);
    return true;
};
bool TreasureChest::removeItem(Item* item) {
    for (int i = 0; i < this->items.size(); i++) {
        if (item == this->items.at(i)) {
            this->items.erase(items.begin() + i);
            return true;
        }
    }
    return false;
};
bool TreasureChest::removeItem(string name) {
    for (int i = 0; i < this->items.size(); i++) {
        if ((name == this->items.at(i)->getName())) { // In case there's 2 item
            this->items.erase(items.begin() + i);
            return true;
        }
    }
    return false;
};

Item* TreasureChest::takeItem(string name) {
    Item* temp = nullptr;
    for (int i = 0; i < this->items.size(); i++) {
        if (name == this->items.at(i)->getName()) {
            temp = items.at(i); // This get a copy of the pointer
            this->items.erase(items.begin() + i); // Remove the item
            return temp;
        }
    }
    return temp;
};
