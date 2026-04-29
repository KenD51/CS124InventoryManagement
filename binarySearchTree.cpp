#include "binarySearchTree.h"

TreeNode::TreeNode(const Item& item) {
    data = item;
    left = nullptr;
    right = nullptr;
}

InventoryBST::InventoryBST() {
    root = nullptr;
}

InventoryBST::~InventoryBST() {
    delete root;
}

void InventoryBST::insert(const Item &item) {

}

std::vector<Item> InventoryBST::traverseBFS() const {

}

std::vector<Item> InventoryBST::traverseDFS() const {}
