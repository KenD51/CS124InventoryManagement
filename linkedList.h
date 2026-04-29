#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "itemType.h"
#include <iostream>

/**
 * @brief Node structure for the linked list.
 */
struct Node {
    Item data;
    Node* next;
    
    // Constructor
    Node(const Item& item) : data(item), next(nullptr) {}
};

/**
 * @class LinkedList
 * @brief A simple singly linked list to store inventory items.
 */
class LinkedList {
private:
    Node* head;

public:
    LinkedList();
    ~LinkedList(); 

    /**
     * @brief Inserts a new item at the end of the list.
     */
    void insert(const Item& item);

    /**
     * @brief Displays all items in the linked list.
     */
    void display() const;
};

#endif // LINKED_LIST_H