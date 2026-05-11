#include "linkedList.h"
#include <iostream>
LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

void LinkedList::insertAtStart(const Item& item) {
    Node* newNode = new Node(item);           //node created
    if (head == nullptr) {                                                  //if empty
        head = newNode;
        tail = newNode;
    }
    else {                                                                  //assigns new head
        newNode->next = head;
        head = newNode;
    }
    count++;
}
void LinkedList::insertAtEnd(const Item& item) {

    Node* newNode = new Node(item);             //creates new node
    if (head == nullptr) {                                                    //if empty
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;                                                 //assigns new tail
        tail = newNode;
    }
    count++;
}

void LinkedList::insertAfter(Node* node, const Item& item) {
    Node* newNode = new Node(item);
    newNode->next = node->next;             //point newNode to the next node
    node->next = newNode;                   //update passed in node to point to the new node
    count++;
}
bool LinkedList::remove(const std::string& id){
    if(head == nullptr) {
        return false;
    }
    if (head->data.getId() == id) {
        Node* nodeToDelete = head;
        head = head->next;

        if (tail == nodeToDelete) {
            tail = nullptr;
        }

        delete nodeToDelete;
        count--;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->data.getId() == id) {
            Node* nodeToDelete = current->next;

            current->next = nodeToDelete->next;

            if (tail == nodeToDelete) {
                tail = current;
            }

            delete nodeToDelete;
            count--;
            return true;
        }
        current = current->next;
    }
    return false;
}

int LinkedList::getCount() const {
    return count;
}
LinkedList::Node* LinkedList::getHead() const {
    return head;
}
LinkedList::Node* LinkedList::getTail() const {
    return tail;
}
void LinkedList::setHead(Node* newHead) {
    head = newHead;
}
void LinkedList::setTail(Node* newTail) {
    tail = newTail;
}
void LinkedList::display() const {
    Node* current = head;
    while (current != nullptr) {
        std::cout << "ID: " << current->data.getId() << std::endl;
        std::cout << "Name: " << current->data.getName() << std::endl;
        std::cout << "Category: " << current->data.getCategory() << std::endl;
        std::cout << "Quantity: " << current->data.getQuantity() << std::endl;
        std::cout << "Min Stock Threshold: " << current->data.getMinStockThreshold() << std::endl;
        current = current->next;
    }
}

//MEMORY LEAKS
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}