#ifndef ITEM_TYPES_H
#define ITEM_TYPES_H

#include <string>


struct Item {
    std::string id; //Using alias here, product id is a string to uniquely identify the object (item)
    std::string name; // Name of the item
    std::string category;   // Category of the item 
    int currentQuantity;    // Current quantity of the item in stock
    int minStockThreshold; // Minimum stock threshold for the item, used for restocking alerts//
};

#endif // ITEM_TYPES_H
