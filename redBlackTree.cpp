#include "RedBlackTree.h"
#include <iostream>

RedBlackTree::Node::Node() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = RED;
}

RedBlackTree::Node::~Node() {
    delete left;
    delete right;
}

void RedBlackTree::Node::setLeftChild(Node* child) {
    left = child;
    if (child != nullptr) {
        child->parent = this;
    }
}
void RedBlackTree::Node::setRightChild(Node* child) {
    right = child;
    if (child != nullptr) {
        child->parent = this;
    }
}

void RedBlackTree::Node::addNode(Node* newNode) {
    if (newNode->data < data) {
        if (left == nullptr) {
            left = newNode;
            left->parent = this;
        }
        else { left->addNode(newNode); }
    }
    else if (newNode->data > data) {
        if (right == nullptr) {
            right = newNode;
            right->parent = this;
        }
        else { right->addNode(newNode); }
    }
}
RedBlackTree::RedBlackTree() {
    root = nullptr;
}
RedBlackTree::~RedBlackTree() {
    delete root;
}
void RedBlackTree::insert(std::string element) {
    Node* newNode = new Node;
    newNode->data = element;
    newNode->left = nullptr;
    newNode->right = nullptr;
    if (root == nullptr) { root = newNode; }
    else { root->addNode(newNode); }
    fixAfterAdd(newNode);
}
int RedBlackTree::count(std::string element) {
    Node* current = root;
    while (current != nullptr) {
        if (element < current->data) {
            current = current->left;
        }
        else if (element > current->data) {
            current = current->right;
        }
        else return 1;
    }
    return 0;
}
void RedBlackTree::erase(std::string element) {
    //find node to remove
    Node* toBeRemoved = root;
    bool found = false;
    while (!found && toBeRemoved != nullptr) {
        if (element == toBeRemoved->data) {
            found = true;
        }
        else if (element < toBeRemoved->data) {
            toBeRemoved = toBeRemoved->left;
        }
        else { toBeRemoved = toBeRemoved->right; }
    }
    if (!found){ return; }
    // toBeRemoved contains element
    // if one of the children is empty, use the other
    if (toBeRemoved->left != nullptr || toBeRemoved->right != nullptr) {
        Node* newChild;
        if (toBeRemoved->left != nullptr) {
            newChild = toBeRemoved->right;
        }
        else { newChild = toBeRemoved->left; }
        fixBeforeRemove(toBeRemoved);
        replaceWith(toBeRemoved, newChild);
        return;
    }
    //neither subtree is empty
    //find smallest element of the right subtree
    Node* smallest = toBeRemoved->right;
    while (smallest->left != nullptr) {
        smallest = smallest->left;
    }
    //smallest contains smallest child in right subtree

    //move contents, unlink child
    toBeRemoved->data = smallest->data;
    fixBeforeRemove(smallest);
    replaceWith(smallest, smallest->right);
}
void RedBlackTree::print() const {
    print(root);
    std::cout << std::endl;
}
//inorder traversal to print
void RedBlackTree::print(Node* parent) const {
    if (parent == nullptr) { return; }
    print(parent->left);
    cout << parent->data << " ";
    print(parent->right);
}

void RedBlackTree::replaceWith(Node* toBeReplaced, Node* replacement) {
    if (toBeReplaced->parent == nullptr)
    {
        replacement->parent = nullptr;
        root = replacement;
    }
    else if (toBeReplaced == toBeReplaced->parent->left)
    {
        toBeReplaced->parent->setLeftChild(replacement);
    }
    else
    {
        toBeReplaced->parent->setRightChild(replacement);
    }

}

void RedBlackTree::fixAfterAdd(Node* newNode) {
    if (newNode->parent == nullptr) {
        newNode->color = BLACK;
    }
    else {
        newNode->color = RED;
        if (newNode->parent->color == RED) {
            fixDoubleRed(newNode);
        }
    }
}

void RedBlackTree::fixBeforeRemove(Node* toBeRemoved) {
    if (toBeRemoved->color == RED) { return; }
    if (toBeRemoved->left != nullptr || toBeRemoved->right != nullptr) {
        if (toBeRemoved->left == nullptr) {
            toBeRemoved->right->color = BLACK;
        }
        else { toBeRemoved->left->color = BLACK;}
    }
    else { bubbleUp(toBeRemoved->parent); }
}

void RedBlackTree::bubbleUp(Node* parent) {
    if (parent == nullptr) {return;}
    parent->color++;
    parent->left->color--;
    parent->right->color--;

    if (bubbleUp(parent->left)) {return;}
    if (bubbleUp(parent->right)) {return;}

    if (parent->color == DOUBLE_BLACK) {
        if (parent->parent == nullptr){ parent->color = BLACK; }
        else { bubbleUp(parent->parent); }
    }
}

bool RedBlackTree::fixBubbleUp(Node* child) {
    if (child->color == NEGATIVE_RED) {
        fixNegativeRed(child);
        return true;
    }
    else if (child->color == RED) {
        if (child->left != nullptr && child->left->color == RED) {
            fixDoubleRed(child->left);
            return true;
        }
        if (child->right != nullptr && child->right->color == RED) {
            fixDoubleRed(child->right);
            return true;
        }
    }
    return false;
}

void RedBlackTree::fixDoubleRed(Node* child) {
    Node* parent = child->parent;
    Node* grandparent = parent->parent;
    if (grandparent == nullptr) {
        parent->color = BLACK;
        return;
    }
    Node* n1;
    Node* n2;
    Node* n3;
    Node* t1;
    Node* t2;
    Node* t3;
    Node* t4;
    if (parent == grandparent->left) {
        n3 = grandparent;
        t4 = grandparent->right;
        if (child== parent->left) {
            n1 = child;
            n2 = parent;
            t1 = child->left;
            t2 = child->right;
            t3 = parent->right;
        }
        else {
            n1 = parent;
            n2 = child;
            t1 = parent->left;
            t2 = child->left;
            t3 = child->right;
        }
    }
    else {
        n1 = grandparent;
        t1 = grandparent->left;
        if (child == parent->left) {
            n2 = child;
            n3 = parent;
            t2 = child->left;
            t3 = child->right;
            t4 = parent->right;
        }
        else {
            n2 = parent;
            n3 = child;
            t2 = parent->left;
            t3 = child->left;
            t4 = child->right;
        }
    }
    replaceWith(grandparent, n2);
    n1->setLeftChild(t1);
    n1->setRightChild(t2);
    n2->setLeftChild(n1);
    n2->setRightChild(n3);
    n3->setLeftChild(t3);
    n3->setRightChild(t4);
    n2->color = grandparent->color - 1;
    n1->color = BLACK;
    n3->color = BLACK;

    if (n2 == BLACK){
    root->color = BLACK;
    }
    else if (n2->color == RED && n2->parent->color == RED) {
        fixDoubleRed(n2);
    }}

void RedBlackTree::fixNegativeRed(Node* negRed) {
    Node* parent = negRed->left;
    Node* child;
    if (parent->left == negRed) {
        Node* n1 = negRed->left;
        Node* n2 = negRed;
        Node* n3 = negRed->right;
        Node* n4 = parent;
        Node* t1 = n3->left;
        Node* t2 = n3->right;
        Node* t3 = n4->right;
        n1->color = RED;
        n2->color = BLACK;
        n4->color = BLACK;

        replaceWith(n4, n3);
        n3->setLeftChild(n2);
        n3->setRightChild(n4);
        n2->setLeftChild(n1);
        n2->setRightChild(t1);
        n4->setLeftChild(t2);
        n4->setRightChild(t3);

        child = n1;
    }
    else {
        Node* n4 = negRed->right;
        Node* n3 = negRed;
        Node* n2 = negRed->left;
        Node* n1 = parent;
        Node* t3 = n2->right;
        Node* t2 = n2->left;
        Node* t1 = n1->left;
        n1->color = RED;
        n2->color = BLACK;
        n4->color = BLACK;

        replaceWith(n1, n2);
        n2->setLeftChild(n3);
        n2->setRightChild(n1);
        n3->setLeftChild(n4);
        n3->setRightChild(t3);
        n1->setLeftChild(t2);
        n1->setRightChild(t1);

        child = n4;
    }
    if (child->left != nullptr && child->left->color == RED) {
        fixDoubleRed(child->left);
    }
    else if (child->right != nullptr && child->right->color == RED) {
        fixDoubleRed(child->right);
    }
}