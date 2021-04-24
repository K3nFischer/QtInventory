#include "inventory.hpp"
#include <fstream>

Inventory::Inventory() {

}

Inventory::Inventory(std::string filename){
    std::ifstream inputStream;
    inputStream.open(filename, std::ios::in);
    if( ! inputStream.is_open()) {
        exit(2);
    }


    inputStream.close();
}

std::vector<Item> Inventory::lookup(std::string key){
    std::vector<Item> searchResults;
    for(auto it = items.begin(); it != items.end(); ++it){
        if(it->getName().find(key) != std::string::npos)
            searchResults.push_back(*it);
    }
    return searchResults;
}
