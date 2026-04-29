#ifndef CS124INVENTORYMANAGEMENT_REDBLACKTREE_H
#define CS124INVENTORYMANAGEMENT_REDBLACKTREE_H

#include <string>
#include <vector>

const int BLACK = 1;
const int RED = 0;
const int NEGATIVE_RED = -1;
const int DOUBLE_BLACK = -2;

/*
   This class implements a red-black tree.
*/
class RedBlackTree
{
public:
   /**
      Constructs an empty tree.
   */
   RedBlackTree();
   ~RedBlackTree();
   RedBlackTree(const RedBlackTree& other); // Not implemented
   RedBlackTree& operator=(const RedBlackTree& other);  // Not implemented

   /**
      Inserts a new element into the tree.
      @param element the element to insert
   */
   void insert(string element);

   /**
      Tries to find an element in the tree.
      @param element the element to find
      @return 1 if the element is contained in the tree, 0 otherwise
   */
   int count(string element) const;

   /**
      Tries to remove an element from the tree. Does nothing
      if the element is not contained in the tree.
      @param element the element to remove
   */
   void erase(string element);

   /**
      Prints the contents of the tree in sorted order.
   */
   void print() const;

private:
   /**
   A node of a red-black tree stores a data item and references
   of the child nodes to the left and to the right. The color
   is the "cost" of passing the node; 1 for black or 0 for red.
   Temporarily, it may be set to 2 or -1.
*/
   class Node {
   public:
      /**
         Constructs a red node with no data.
      */
      Node();
      ~Node();

      // These members are public for testing
      /**
         Sets the left child and updates its parent reference.
         @param child the new left child
      */
      void setLeftChild(Node* child);

      /**
         Sets the right child and updates its parent reference.
         @param child the new right child
      */
      void setRightChild(Node* child);

      string data;
      Node* left;
      Node* right;
      Node* parent;
      int color;

   private:
      /**
         Adds a node as a child of this node.
         @param new_node the node to add
      */
      void addNode(Node* newNode);
   };
   /**
      Prints a node and all of its descendants in sorted order.
      @param parent the root of the subtree to print
   */
   void print(Node* parent) const;

   /**
      Updates the parent's and replacement node's
      links when this node is replaced.
      Also updates the root reference if it is replaced.
      @param to_be_replaced the node that is to be replaced
      @param replacement the node that replaces that node
   */
   void replaceWith(Node* toBeReplaced, Node* replacement);

   /**
      Restores the tree to a red-black tree after a node has been added.
      @param new_node the node that has been added
   */
   void fixAfterAdd(Node* newNode);

   /**
     Fixes the tree so that it is a red-black tree after a node has been removed.
     @param to_be_removed the node that is to be removed
   */
   void fixBeforeRemove(Node* toBeRemoved);

   /**
      Move a charge from two children of a parent.
      @param parent a node with two children, or
      nullptr (in which case nothing is done)
   */
   void bubbleUp(Node* parent);

   /**
      Fixes a negative-red or double-red violation introduced by bubbling up.
      @param child the child to check for negative-red
      or double-red violations
      @return true if the tree was fixed
   */
   bool bubbleUpFix(Node* child);

   /**
      Fixes a "double red" violation.
      @param child the child with a red parent
   */
   void fixDoubleRed(Node* child);

   /**
      Fixes a "negative red" violation.
      @param neg_red the negative red node
   */
   void fixNegativeRed(Node* negRed);

public: // for testing
   Node* root;
};














#endif //CS124INVENTORYMANAGEMENT_REDBLACKTREE_H