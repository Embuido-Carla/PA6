//Carla Embuido
//7-8-2025
//Purpose: Header file for the binary search tree implementation

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "binarytree.h"
#include "linkedtreenode.h"
#include "tree.h"
#include <iostream>
using namespace std;

template <class ItemType>
class BinarySearchTree : public BinaryTree<ItemType> {
protected:
    using BinaryTree<ItemType>::rootPtr;

    //Helper function to transverse the tree from the Left, Root, Right
    void inorderHelper(LinkedTreeNode<ItemType>* subTreePtr) const {
        if (subTreePtr != nullptr) {
            // Traverse left subtree
            inorderHelper(subTreePtr->getLeftChildPtr());
            
            // Visit the root node
            cout << subTreePtr->getItem() << " ";
            
            // Traverse right subtree
            inorderHelper(subTreePtr->getRightChildPtr());
        }
    }

    //Helpers function to transverse the tree from the Root, Left, Right
    void preorderHelper(LinkedTreeNode<ItemType>* subTreePtr) const {
        if (subTreePtr != nullptr) {
            // Visit the root node
            cout << subTreePtr->getItem() << " ";
            
            // Traverse left subtree
            preorderHelper(subTreePtr->getLeftChildPtr());
            
            // Traverse right subtree
            preorderHelper(subTreePtr->getRightChildPtr());
        }
    }

    //Helpers function to transverse the tree from the Left, Right, Root
    void postorderHelper(LinkedTreeNode<ItemType>* subTreePtr) const {
        if (subTreePtr != nullptr) {
            // Traverse left subtree
            postorderHelper(subTreePtr->getLeftChildPtr());
            
            // Traverse right subtree
            postorderHelper(subTreePtr->getRightChildPtr());
            
            // Visit the root node
            cout << subTreePtr->getItem() << " ";
        }
    }

    //Helpers function to add a new entry to the tree recursively
    LinkedTreeNode<ItemType>* addHelper(const ItemType& newEntry, LinkedTreeNode<ItemType>* subTreePtr) {
        //base case:
        if(subTreePtr == nullptr) {
            //Create new node and set it as root
            return new LinkedTreeNode<ItemType>(newEntry);
        }

        //Recursive case:
        //if new entry is LESS THAN root's value
        if (newEntry < subTreePtr->getItem()) {
            //go LEFT
            LinkedTreeNode<ItemType>* left = addHelper(newEntry, subTreePtr->getLeftChildPtr());
            subTreePtr->setLeftChildPtr(left);
        }
        //if new entry is MORE THAN root's value
        else if (newEntry > subTreePtr->getItem()) {
            //go RIGHT
            LinkedTreeNode<ItemType>* right = addHelper(newEntry, subTreePtr->getRightChildPtr());
            subTreePtr->setRightChildPtr(right);
        }
        //If newEntry is equal to root's value NO ADDING NO DUPLICATES
        return subTreePtr;
    }

    //Function to remove an entry from the tree via recursion
    LinkedTreeNode<ItemType>* removeHelper(const ItemType& anEntry, LinkedTreeNode<ItemType>* subTreePtr) {
        //Base case
        if (subTreePtr == nullptr) {
            return nullptr;
        }

        //Searching through recursively
        if (anEntry < subTreePtr->getItem()) {
            LinkedTreeNode<ItemType>* left = removeHelper(anEntry, subTreePtr->getLeftChildPtr());
            subTreePtr->setLeftChildPtr(left);
        } 
        else if (anEntry > subTreePtr->getItem()) {
            LinkedTreeNode<ItemType>* right = removeHelper(anEntry, subTreePtr->getRightChildPtr());
            subTreePtr->setRightChildPtr(right);
        }
        //ONCE node wanted to be deleted is found
        else {
            //Create pointer to the node to delete to avoid memory leak
            LinkedTreeNode<ItemType>* nodeToDelete = subTreePtr;

            //CASE 1: Leaf
            if (nodeToDelete->isLeaf()) {
                delete nodeToDelete;
                return nullptr;
            }
            //CASE 2: Only RIGHT child
            else if (nodeToDelete->getLeftChildPtr() == nullptr) {
                LinkedTreeNode<ItemType>* right = nodeToDelete->getRightChildPtr();
                delete nodeToDelete;
                return right;
            }
            //CASE 3: Only LEFT child
            else if (nodeToDelete->getRightChildPtr() == nullptr) {
                LinkedTreeNode<ItemType>* left = nodeToDelete->getLeftChildPtr();
                delete nodeToDelete;
                return left;
            }
            //CASE 4: Two children, need to find successor and replace
            else {
                //Find the successor
                LinkedTreeNode<ItemType>* successor = nodeToDelete->getRightChildPtr();
                //Loops until it finds the leftmost node in the right subtree
                while (successor->getLeftChildPtr() != nullptr) {
                    successor = successor->getLeftChildPtr();
                }
                
                //Copy data so we can replace the node to delete to prevent memory leak
                subTreePtr->setItem(successor->getItem());
                
                //Remove the successor
                LinkedTreeNode<ItemType>* right = removeHelper(successor->getItem(), subTreePtr->getRightChildPtr());
                subTreePtr->setRightChildPtr(right);
            }
        }
        return subTreePtr;
    }

    LinkedTreeNode<ItemType>* containsHelper(const ItemType& anEntry, LinkedTreeNode<ItemType>* subTreePtr) const {
        //Base case
        if (subTreePtr == nullptr) {
            return nullptr; //Nothing found
        }

        //When the entry is found
        if (subTreePtr->getItem() == anEntry) {
            return subTreePtr; //return the pointer to the node that contains the value
        }

        //Recursively search left and right subtrees
        if (anEntry < subTreePtr->getItem()) {
            return containsHelper(anEntry, subTreePtr->getLeftChildPtr());
        }
        return containsHelper(anEntry, subTreePtr->getRightChildPtr());
    }

public:
    BinarySearchTree() : BinaryTree<ItemType>() {}

    virtual bool add(const ItemType& newEntry) override {
        LinkedTreeNode<ItemType>* newRoot = addHelper(newEntry, rootPtr);
        if (rootPtr == nullptr) {
            rootPtr = newRoot;
        }
        return newRoot != nullptr;
    }

    virtual bool remove(const ItemType& anEntry) override {
        LinkedTreeNode<ItemType>* newRoot = removeHelper(anEntry, rootPtr);
        if (newRoot != rootPtr) {
            rootPtr = newRoot;
        }
        return newRoot != nullptr;
    }

    virtual bool contains(const ItemType& anEntry) const override {
        return containsHelper(anEntry, rootPtr) != nullptr; //Check if found
    }

    void inorderTraversal() const {
        inorderHelper(rootPtr);
        cout << endl; // For better readability
    }

    void preorderTraversal() const {
        preorderHelper(rootPtr);
        cout << endl; // For better readability
    }

    void postorderTraversal() const {
        postorderHelper(rootPtr);
        cout << endl; // For better readability
    }
};
#endif