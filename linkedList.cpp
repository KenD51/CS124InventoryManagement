#include "linkedList.h"

LinkedList::LinkedList() {
    head == nullptr;
}

LinkedList::insert(const Item& item) {
    head = new Node(item);
}

void LinkedList::display() const {

}