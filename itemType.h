#ifndef ITEM_TYPES_H
#define ITEM_TYPES_H

#include <string>


class Item {
public:
    // constructors
    Item();
    Item(std::string id, std::string name, std::string category, int quantity, int minStockThreshold);
    // destructor
    ~Item();
    // returns ID string
    std::string getId() const;
    // returns name string
    std::string getName() const;
    // returns category string
    std::string getCategory() const;
    // returns quantity int
    int getQuantity() const;
    // returns minimum stock allowance int
    int getMinStockThreshold() const;
private:
    std::string id;         // Using alias here, product id is a string to uniquely identify the object (item)
    std::string name;       // Name of the item
    std::string category;   // Category of the item 
    int quantity;           // Current quantity of the item in stock
    int minStockThreshold;  // Minimum stock threshold for the item, used for restocking alerts//
};

#endif // ITEM_TYPES_H
