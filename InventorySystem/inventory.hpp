#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#include "item.hpp"
#include <vector>

class Inventory
{
public:
    Inventory();
    Inventory(std::string);
    std::vector<Item> lookup(std::string);
    void remove(std::string);
    void destroy(){items.clear();}
    void modify();
    void exportInventory();
private:
    std::vector<Item> items;
};

#endif // INVENTORY_HPP
