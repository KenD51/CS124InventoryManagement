#include "redBlackTree.h"
#include "itemType.h"
#include <iostream>
#include <stack>

RedBlackTree::Node::Node() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = RED;
}

RedBlackTree::Node::Node(const Item& item) {
        data = item;
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

bool RedBlackTree::Node::addNode(Node* newNode) {

    if (newNode->data.getId() < data.getId()) {
        if (left == nullptr) {
            setLeftChild(newNode);
            return true;
        }
        return left->addNode(newNode);
    }
    if (newNode->data.getId() > data.getId()) {
        if (right == nullptr) {
            setRightChild(newNode);
            return true;
        }
        return right->addNode(newNode);

    }
    //duplicate id
    return false;
}

RedBlackTree::RedBlackTree() {
    root = nullptr;
}

RedBlackTree::~RedBlackTree() {
    delete root;
}

void RedBlackTree::insert(const Item& item) {
    Node* newNode = new Node(item);
    if (root == nullptr) {
        root = newNode;
        root->color = BLACK;
        return;
    }
    bool inserted = root->addNode(newNode);
    if (!inserted) {
        delete newNode;
        return;
    }
    fixAfterAdd(newNode);
}

int RedBlackTree::count(const std::string& id) const {
    Node* current = root;
    while (current != nullptr) {
        if (id < current->data.getId()) {
            current = current->left;
        }
        else if (id > current->data.getId()) {
            current = current->right;
        }
        else return 1;
    }
    return 0;
}

Item* RedBlackTree::search(const std::string& id) const {
    Node* current = root;
    while (current != nullptr) {
        if (id < current->data.getId()) {
            current = current->left;
        }
        else if (id > current->data.getId()) {
            current = current->right;
        }
        else {
            return &(current->data);
        }
    }
    return nullptr;
}

void RedBlackTree::erase(const std::string& id) {
    //find node with matching id
    Node* toBeRemoved = root;
    bool found = false;
    while (!found && toBeRemoved != nullptr) {
        if (id == toBeRemoved->data.getId()) {
            found = true;
        }
        else if (id < toBeRemoved->data.getId()) {
            toBeRemoved = toBeRemoved->left;
        }
        else {
            toBeRemoved = toBeRemoved->right;
        }
    }
    if (!found) {
        return;
    }
    // toBeRemoved contains element
    // if one of the children is empty, use the other
    if (toBeRemoved->left == nullptr || toBeRemoved->right == nullptr) {
        Node* newChild;
        if (toBeRemoved->left != nullptr) {
            newChild = toBeRemoved->left;
        }
        else {
            newChild = toBeRemoved->right;
        }

        fixBeforeRemove(toBeRemoved);
        replaceWith(toBeRemoved, newChild);

        toBeRemoved->left = nullptr;
        toBeRemoved->right = nullptr;
        delete toBeRemoved;
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

    Node* newChild = smallest->right;

    fixBeforeRemove(smallest);
    replaceWith(smallest, newChild);

    smallest->left = nullptr;
    smallest->right = nullptr;
    delete smallest;
}

void RedBlackTree::print() const {
    print(root);
    std::cout << std::endl;
}

//inorder traversal to print. 
void RedBlackTree::print(Node* parent) const {
    if (parent == nullptr) { return; }
    print(parent->left);
    std::cout << parent->data.getName();
    print(parent->right);
}

void RedBlackTree::replaceWith(Node* toBeReplaced, Node* replacement) {
    if (toBeReplaced->parent == nullptr)
    {
        root = replacement;
        if (replacement != nullptr) {
            replacement->parent = nullptr;
        }
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
    if (newNode == root) {
        newNode->color = BLACK;
        return;
    }

    newNode->color = RED;

    if (newNode->parent != nullptr && newNode->parent->color == RED) {
        fixDoubleRed(newNode);
    }

    root->color = BLACK;
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
    if (parent == nullptr) {
        return;
    }
    parent->color++;
    if (parent->left != nullptr) {
        parent->left->color--;
    }
    if (parent->right != nullptr) {
        parent->right->color--;
    }

    if (parent->left != nullptr && fixBubbleUp(parent->left)) {
        return;
    }
    if (parent->right != nullptr &&fixBubbleUp(parent->right)) {
        return;
    }

    if (parent->color == DOUBLE_BLACK) {
        if (parent->parent == nullptr) {
            parent->color = BLACK;
        }
        else {
            bubbleUp(parent->parent);
        }
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

    if (n2->color == BLACK){
    root->color = BLACK;
    }
    if (n2->parent != nullptr && n2->color == RED && n2->parent->color == RED) {
        fixDoubleRed(n2);
    }
}

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
void RedBlackTree::DepthFirstSearch() {
    if (root == nullptr) {
        return;
    }
    std::stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        if (current->right) { s.push(current->right);}
        if (current->left) { s.push(current->left);}
        std::cout << current-> data.getId() << " ";
    }
}