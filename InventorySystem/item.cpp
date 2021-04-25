#include "item.hpp"

Item::Item() {
    name = "";
    double retailPrice = 0.0;
    int numberOfItems = 0;
    double wholesalePrice = 0.0;
    std::string manufacturer = "";
}

Item::Item(std::string inputName, double inputRetail, double inputWholesale, std::string inputManufacturer, int inputNumItems) {
    name = inputName;
    retailPrice = inputRetail;
    wholesalePrice = inputWholesale;
    numberOfItems = inputNumItems;
    manufacturer = inputManufacturer;
}
