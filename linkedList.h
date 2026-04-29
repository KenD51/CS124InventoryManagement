#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "itemType.h"

/**
 * @class LinkedList
 * @brief A simple singly linked list to store inventory items.
 */
class LinkedList {

public:
    /**
     * @brief default constructor
     */
    LinkedList();
    /**
     * @brief default destructor
     */
    ~LinkedList(); 

    /**
     * @brief Inserts a new item at the start of the list.
     */
    void insertAtStart(const Item& item);
    /**
     * @brief Inserts a new item at the end of the list.
     */
    void insertAtEnd(const Item& item);
    /**
     * @brief Inserts a new item after specified node of the list.
     */
    void insertAfter(Node* node, const Item& item);
    /**
     * @brief returns count
     */
    int getCount() const;
    /**
     * @brief returns head pointer
     */
    Node* getHead() const;
    /**
     * @brief sets head pointer
     */
    void setHead(Node* newHead);
    /**
     * @brief returns tail pointer
     */
    Node* getTail() const;
    /**
     * @brief sets tail pointer
     */
    void setTail(Node* newTail);
    /**
     * @brief Displays all items in the linked list.
     */
    void display() const;
private:
    struct Node {
        Item data;
        Node* next;

        // Constructor
        Node(const Item& item) : data(item), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;
};

#endif // LINKED_LIST_H