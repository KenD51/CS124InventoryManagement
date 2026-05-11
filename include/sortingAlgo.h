#ifndef SORTING_ALGO_H
#define SORTING_ALGO_H

#include "linkedList.h"

/*
*   Implemented https://www.geeksforgeeks.org/dsa/cpp-program-for-merge-sort-of-linked-lists/
*   This allowed me to learn more about mergeSort with the addition of nodes and recursion.
*/

// Finds the middle of the linked list (used for splitting)
LinkedList::Node* getMiddle(LinkedList::Node* head);

// Merges two sorted linked lists
LinkedList::Node* merge(LinkedList::Node* left, LinkedList::Node* right);

// Merge sort entry function
LinkedList::Node* mergeSort(LinkedList::Node* head);

#endif
