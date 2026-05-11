#include "../include/heapSort.h"

int getLeftChild(int index) {
    return 2 * index + 1;
}

int getRightChild(int index) {
    return 2 * index + 2;
}

void fixHeapByName(std::vector<Item> &inventory, int rootIndex, int lastIndex) {
    Item rootValue = inventory[rootIndex];

    int index = rootIndex;
    bool done = false;

    while (!done) {
        int leftChildIndex = getLeftChild(index);
        if (leftChildIndex <= lastIndex) {
            int rightChildIndex = getRightChild(index);
            // grabs child with larger alphabetical name
            if (rightChildIndex <= lastIndex && inventory[leftChildIndex].getName() < inventory[rightChildIndex].getName()) {
                leftChildIndex = rightChildIndex;
            }
            // moves larger child up if larger than root
            if (rootValue.getName() < inventory[leftChildIndex].getName()) {
                inventory[index] = inventory[leftChildIndex];
                index = leftChildIndex;
            }

            else {
                done = true;
            }
        }
        else {
            done = true;
        }
    }
    inventory[index] = rootValue;
}

void heapSortByName(std::vector<Item>& inventory) {
    // base case
    if (inventory.empty()) {
        return;
    }
    int n = static_cast<int>(inventory.size() - 1);
    // Max heap build by name
    for (int i  = (n - 1) / 2; i >= 0; i--) {
        fixHeapByName(inventory, i, n);
    }
    // Moves largest element and check children
    while (n > 0){
        Item temp = inventory[0];
        inventory[0] = inventory[n];
        inventory[n] = temp;

        n--;

        fixHeapByName(inventory, 0, n);
    }
}