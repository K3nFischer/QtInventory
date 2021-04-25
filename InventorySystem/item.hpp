#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>

class Item {
public:
    Item();
    Item(std::string name, double retailPrice, double wholesalePrice, std::string manufacturer, int numberOfItems);
    std::string getName(){return name;}
    double getRetailPrice(){return retailPrice;}
    int returnItemCount(){return numberOfItems;}
    double getWholesalePrice(){return wholesalePrice;}
    std::string getManufacturer(){return manufacturer;}
private:
    std::string name;
    double retailPrice;
    int numberOfItems;
    double wholesalePrice;
    std::string manufacturer;
};

#endif // ITEM_HPP
