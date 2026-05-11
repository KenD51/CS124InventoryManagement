
#ifndef CS124INVENTORYMANAGEMENT_HEAPSORT_H
#define CS124INVENTORYMANAGEMENT_HEAPSORT_H

#include "itemType.h"
#include <vector>
/**
 * Heapsort largely implemented based off of ZyBooks and adjusted to deal with a vector of Item objects and builds the
 * max heap based off of Item names
 *                                                 -- credit to ZyBooks --
 */

/**
 *@param int index
 *@returns left child index
 */
int getLeftChild(int index);
/**
 *@param int index
 *@returns right child index
 */
int getRightChild(int index);
/**
 *@param vector of Items, int root index, int last index
 *@returns void
 */
void fixHeapByName(std::vector<Item>& inventory, int rootIndex, int lastIndex);
/**
 *@param vector of Items
 *@returns void
 */
void heapSortByName(std::vector<Item>& inventory);


#endif //CS124INVENTORYMANAGEMENT_HEAPSORT_H