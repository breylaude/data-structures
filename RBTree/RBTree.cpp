#include <iostream>
#include "RBTree.h"
using namespace std;

RBTree ::RBTree()
{
    root = nullptr;
    cr = cl = cp = "  ";
    cr[0] = 218;
    cr[1] = 196;
    cl[0] = 192;
    cl[1] = 196;
    cp[0] = 179;
}

RBNode *RBTree::getRoot()
{
    return this->root;
}

void RBTree ::deleteTree(RBNode *node)
{
    if (node != nullptr)
    {
        deleteTree(node->rightChild);
        deleteTree(node->leftChild);
        delete node;
    }
}

bool RBTree::isEmpty()
{
    if (root == nullptr)
        return true;
    return false;
}

// Get the sibling of the particular node
RBNode *RBTree::getSibling(RBNode *node)
{
    if (node->parent == nullptr)
    {
        return nullptr;
    }

    if (node == node->parent->leftChild)
    {
        return node->parent->rightChild;
    }
    return node->parent->leftChild;
}

// Find the node in the tree by value
RBNode *RBTree::find(int value)
{
    RBNode *temp;

    temp = root;
    while ((temp != nullptr) && (temp->data != value))
    {
        if (value < temp->data)
        {
            temp = temp->leftChild;
        }
        else
        {
            temp = temp->rightChild;
        }
    }
    if (temp == nullptr)
        return nullptr;
    return temp;
}

// Find minimum value in the tree
RBNode *RBTree::findMin(RBNode *nodeToFind)
{
    if (nodeToFind != nullptr)
    {
        while (nodeToFind->leftChild != nullptr)
        {
            nodeToFind = nodeToFind->leftChild;
        }
    }
    return nodeToFind;
}

// Find the successor of the given node
RBNode *RBTree::findSuccessor(RBNode *node)
{
    RBNode *temp;

    if (node != nullptr)
    {
        // If there is right son, return the minimum value in right subtree
        if (node->rightChild != nullptr)
        {
            return findMin(node->rightChild);
        }
        // If there is no right son serch as long as we comr from right size
        else
        {
            temp = node->parent;
            while ((temp != nullptr) && (node == temp->rightChild))
            {
                node = temp;
                temp = temp->parent;
            }
            return temp;
        }
    }
    return nullptr;
}

// Perform left rotation on the given node
void RBTree::leftRotation(RBNode *rotatingNode)
{
    RBNode *rightChildOfRotatingNode = rotatingNode->rightChild, *tempParent = rotatingNode->parent;

    if (rightChildOfRotatingNode)
    {
        rotatingNode->rightChild = rightChildOfRotatingNode->leftChild;
        if (rotatingNode->rightChild)
            rotatingNode->rightChild->parent = rotatingNode;

        rightChildOfRotatingNode->leftChild = rotatingNode;
        rightChildOfRotatingNode->parent = tempParent;
        rotatingNode->parent = rightChildOfRotatingNode;

        if (tempParent)
        {
            if (tempParent->leftChild == rotatingNode)
                tempParent->leftChild = rightChildOfRotatingNode;
            else
                tempParent->rightChild = rightChildOfRotatingNode;
        }
        else
            root = rightChildOfRotatingNode;
    }
}

// Perform right rotation on the given node
void RBTree::rightRotation(RBNode *rotatingNode)
{
    RBNode *leftOfRotatingNode = rotatingNode->leftChild, *tempParent = rotatingNode->parent;

    if (leftOfRotatingNode)
    {
        rotatingNode->leftChild = leftOfRotatingNode->rightChild;
        if (rotatingNode->leftChild)
            rotatingNode->leftChild->parent = rotatingNode;

        leftOfRotatingNode->rightChild = rotatingNode;
        leftOfRotatingNode->parent = tempParent;
        rotatingNode->parent = leftOfRotatingNode;

        if (tempParent)
        {
            if (tempParent->leftChild == rotatingNode)
                tempParent->leftChild = leftOfRotatingNode;
            else
                tempParent->rightChild = leftOfRotatingNode;
        }
        else
            root = leftOfRotatingNode;
    }
}

// Deletes the given node
void RBTree::deleteElement(RBNode *deletingNode)
{
    RBNode *helperNode;
    if (deletingNode->leftChild != nullptr and deletingNode->rightChild != nullptr)
        helperNode = findSuccessor(deletingNode->rightChild);

    // When deleting node is a leaf
    if (deletingNode->leftChild == nullptr and deletingNode->rightChild == nullptr)
        helperNode = nullptr;

    // When deleting node has single child
    if (deletingNode->leftChild != nullptr)
        helperNode = deletingNode->leftChild;
    else
        helperNode = deletingNode->rightChild;

    // Returns true when both both deletingNode and helperNode are black
    bool areBothBlack = ((helperNode == nullptr or helperNode->color == BLACK) and (deletingNode->color == BLACK));
    RBNode *parent = deletingNode->parent;

    if (helperNode == nullptr)
    {
        if (deletingNode == root)
        {
            // deletingNode is root, making root null
            root = nullptr;
        }
        else
        {
            if (areBothBlack)
            {
                // deletingNode is leaf, fix double black at deletingNode
                fixDoubleBlack(deletingNode);
            }
            else
            {
                // helperNode or deletingNode is red
                if (getSibling(deletingNode) != nullptr)
                    // Sibling is not null, make it red
                    getSibling(deletingNode)->color = RED;
            }

            // Delete deletingNode from the tree
            if (deletingNode == deletingNode->parent->leftChild)
            {
                parent->leftChild = nullptr;
            }
            else
            {
                parent->rightChild = nullptr;
            }
        }
        delete deletingNode;
        return;
    }

    if (deletingNode->leftChild == nullptr or deletingNode->rightChild == nullptr)
    {
        // deletingNode has 1 child
        if (deletingNode == root)
        {
            // deletingNode is root
            deletingNode->data = helperNode->data;
            deletingNode->leftChild = deletingNode->rightChild = nullptr;
            delete helperNode;
        }
        else
        {
            if (deletingNode == deletingNode->parent->leftChild)
            {
                parent->leftChild = helperNode;
            }
            else
            {
                parent->rightChild = helperNode;
            }
            delete deletingNode;
            helperNode->parent = parent;
            if (areBothBlack)
            {
                // Fix double black at helperNode
                fixDoubleBlack(helperNode);
            }
            else
            {
                // helperNode or deletingNode red, color helperNode black
                helperNode->color = BLACK;
            }
        }
        return;
    }

    // deletingNode has 2 children, swap values with successor and recurse
    swap(helperNode->data, deletingNode->data);
    deleteElement(helperNode);
}

void RBTree::fixDoubleBlack(RBNode *x)
{
    if (x == root)
        // Reached root
        return;

    RBNode *sibling = getSibling(x), *parent = x->parent;
    if (sibling == nullptr)
    {
        // No sibiling, double black pushed up
        fixDoubleBlack(parent);
    }
    else
    {
        if (sibling->color == RED)
        {
            // Sibling is red
            parent->color = RED;
            sibling->color = BLACK;
            if (sibling == sibling->parent->leftChild)
            {
                rightRotation(parent);
            }
            else
            {
                leftRotation(parent);
            }
            fixDoubleBlack(x);
        }
        else
        {
            // Sibling is black
            if ((sibling->leftChild != nullptr && sibling->leftChild->color == RED) || (sibling->rightChild != nullptr && sibling->rightChild->color == RED))
            {
                // There is at least one red child
                if (sibling->leftChild != nullptr and sibling->leftChild->color == RED)
                {
                    if (sibling == sibling->parent->leftChild)
                    {
                        sibling->leftChild->color = sibling->color;
                        sibling->color = parent->color;
                        rightRotation(parent);
                    }
                    else
                    {
                        sibling->leftChild->color = parent->color;
                        rightRotation(sibling);
                        leftRotation(parent);
                    }
                }
                else
                {
                    if (sibling == sibling->parent->leftChild)
                    {
                        sibling->rightChild->color = parent->color;
                        leftRotation(sibling);
                        rightRotation(parent);
                    }
                    else
                    {
                        sibling->rightChild->color = sibling->color;
                        sibling->color = parent->color;
                        leftRotation(parent);
                    }
                }
                parent->color = BLACK;
            }
            else
            {
                // 2 black children
                sibling->color = RED;
                if (parent->color == BLACK)
                    fixDoubleBlack(parent);
                else
                    parent->color = BLACK;
            }
        }
    }
}

// Helper for the element insertion
void RBTree::insertElement(int value)
{
    // Create new node with value
    RBNode *newNode = new RBNode(value);

    // Insert this node like to the normal BST
    root = insertElementNormalBST(root, newNode);

    // Restore the red-black tree properties
    restoreRBTreeProperties(newNode);
}

RBNode *RBTree::insertElementNormalBST(RBNode *rootB, RBNode *newNode)
{
    if (rootB == nullptr)
        return newNode;

    if (newNode->data <= rootB->data)
    {
        rootB->leftChild = insertElementNormalBST(rootB->leftChild, newNode);
        rootB->leftChild->parent = rootB;
    }
    else if (newNode->data > rootB->data)
    {
        rootB->rightChild = insertElementNormalBST(rootB->rightChild, newNode);
        rootB->rightChild->parent = rootB;
    }
    return rootB;
}

void RBTree::restoreRBTreeProperties(RBNode *&newNode)
{
    RBNode *parent = nullptr;
    RBNode *grand_parent = nullptr;
    RBNode *uncle = nullptr;

    while ((newNode != root) && (newNode->color != BLACK) && (newNode->parent->color == RED))
    {
        parent = newNode->parent;
        grand_parent = newNode->parent->parent;

        if (parent == grand_parent->leftChild)
        {
            uncle = grand_parent->rightChild;

            if (uncle != nullptr && uncle->color == RED)
            {
                grand_parent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grand_parent;
            }

            else
            {
                if (newNode == parent->rightChild)
                {
                    leftRotation(parent);
                    newNode = parent;
                    parent = newNode->parent;
                }

                rightRotation(grand_parent);
                swap(parent->color, grand_parent->color);
                newNode = parent;
            }
        }

        else
        {
            uncle = grand_parent->leftChild;

            if ((uncle != nullptr) && uncle->color == RED)
            {
                grand_parent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grand_parent;
            }

            else
            {
                if (newNode == parent->leftChild)
                {
                    rightRotation(parent);
                    newNode = parent;
                    parent = newNode->parent;
                }

                leftRotation(grand_parent);
                swap(parent->color, grand_parent->color);
                newNode = parent;
            }
        }
    }
    root->color = BLACK;
}

void RBTree::inorderH(string sp, string sn, RBNode *node)
{
    string t;
    char color;

    if (node != nullptr)
    {
        t = sp;
        if (sn == cr)
            t[t.length() - 2] = ' ';
        inorderH(t + cp, cr, node->rightChild);

        t = t.substr(0, sp.length() - 2);
        node->color == RED ? color = 'R' : color = 'B';
        cout << t << sn << color << ":" << node->data << endl;

        t = sp;
        if (sn == cl)
            t[t.length() - 2] = ' ';
        inorderH(t + cp, cl, node->leftChild);
    }
}

void RBTree::inorder()
{
    inorderH("", "", root);
}