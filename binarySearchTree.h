#ifndef INVENTORY_BST_H
#define INVENTORY_BST_H

#include "ItemType.h"
#include <string>
#include <vector>

/**
 * @brief Tree node structure for the Binary Search Tree.
 */
struct TreeNode {
    Item data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(const Item& item);
};

/**
 * @class InventoryBST
 * @brief Manages a hierarchy of items, sorted by product ID.
 */
class InventoryBST {
    private:
        TreeNode* root;
    
        //In zybooks we have a helper function for dfs if we're doing this so I added this here. Remove if we're doing BFS
        void dfsHelper(TreeNode* node, std::vector<Item>& result) const;

    public:
        InventoryBST();
        ~InventoryBST(); // Defualt destructor but we will need to implement a function for destroying it.

        /**
         * @brief Inserts a new item into the BST based on its ID.
        */
        void insert(const Item& item);

        /**
         * @brief Performs a Depth-First Search (In-order traversal).
         * @return A vector of items in DFS order.
         */
        std::vector<Item> traverseDFS() const;

        /**
         * @brief Performs a Breadth-First Search (Level-order traversal) using a queue.
         * @return A vector of items in BFS order.
        */
        std::vector<Item> traverseBFS() const;
};

#endif // INVENTORY_BST_H