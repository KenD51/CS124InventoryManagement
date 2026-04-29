#ifndef CS124INVENTORYMANAGEMENT_CSVFUNCTIONS_H
#define CS124INVENTORYMANAGEMENT_CSVFUNCTIONS_H
#include <string>

#include "linkedList.h"
#include "RedBlackTree.h"

bool loadFromFile(const std::string& filename, LinkedList& inventoryList, RedBlackTree& inventoryTree);

std::string getFilename();

#endif //CS124INVENTORYMANAGEMENT_CSVFUNCTIONS_H
