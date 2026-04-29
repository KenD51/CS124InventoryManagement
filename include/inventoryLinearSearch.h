#ifndef INVENTORY_ALGORITHMS_H
#define INVENTORY_ALGORITHMS_H

#include "itemType.h"
#include "sortingAlgo.h"
#include <vector>
#include <string>

/**
 * @class InventoryAlgorithms
 * @brief Class containing search and sorting algorithms for the inventory.
 */
class InventoryAlgorithms {

//Yo i don't think we need a private here boys
public:
    // Constructor and Destructor
    InventoryAlgorithms();
    ~InventoryAlgorithms();

    /**
     * @brief Performs a linear search to find an item by its ID.
     * @param inventory The vector of items to search.
     * @param targetId The ID to look for.
     * @return The index of the item if found, or -1 if not found.
     */
    int linearSearch(const std::vector<Item>& inventory, const std::string& targetId);

    /**
     * @brief Sorts the inventory using a linear/binary logic sorting algorithm. So we can use quicksort or merge if we want.
     * @param inventory The vector of items to sort in-place.
     */
    void sortInventoryByID(std::vector<Item>& inventory);
    
    //I added this below as I will need to call this function to help calculate urgency for the restock priority queue. Seems right to put this here.

    /**
     * @brief Sorts the inventory by quantity to prioritize restocking or track overstock.
     * @param inventory The vector of items to sort in-place.
     */
    void sortInventoryByQuantity(std::vector<Item>& inventory);
};

#endif // INVENTORY_ALGORITHMS_H
