#include "sortingAlgo.h"
#include "linkedList.h"

// Merge function
LinkedList::Node* merge(LinkedList::Node* left, LinkedList::Node* right) {
    if (!left) return right;
    if (!right) return left;

    // SORT BY ID (simple and direct)
    if (left->data.getQuantity() < right->data.getQuantity()) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

LinkedList::Node* getMiddle(LinkedList::Node* head) {
    if (!head) return nullptr;

    LinkedList::Node* slow = head;
    LinkedList::Node* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// Recursive merge sort
LinkedList::Node* mergeSort(LinkedList::Node* head) {
    if (!head || !head->next)
        return head;

    LinkedList::Node* mid = getMiddle(head);
    LinkedList::Node* rightHalf = mid->next;
    mid->next = nullptr;

    LinkedList::Node* left = mergeSort(head);
    LinkedList::Node* right = mergeSort(rightHalf);

    return merge(left, right);
}
