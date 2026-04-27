#ifndef ITEM_TYPES_H
#define ITEM_TYPES_H

#include <string>


//I am using the using keyword here, to denote that productID is a an alias for a string for easier readability.
using ProductID = std::string;

typedef int ProductID;
/**
 * I believe this has the necessary attributes for a basic item stored in the warehouse.
 */
class Item {
    ProductID id; //Using alias here, product id is a string to uniquely identify the object (item)
    std::string name; // Name of the item
    std::string category;   // Category of the item 
    int currentQuantity;    // Current quantity of the item in stock
    int minStockThreshold; // Minimum stock threshold for the item, used for restocking alerts//
};

#endif // ITEM_TYPES_H