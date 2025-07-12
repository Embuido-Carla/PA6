//Carla Embuido
//7-8-2025
//Purpose: Regular binary tree implementation

#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "tree.h"
#include "linkedtreenode.h"
using namespace std;

template<class ItemType>
class BinaryTree : public TreeInterface<ItemType> {
protected:
    LinkedTreeNode<ItemType>* rootPtr;
    
    //Helper function to get the height of the tree recursively
    int getHeightHelper(LinkedTreeNode<ItemType>* subTreePtr) const {
        if (subTreePtr == nullptr) {
            return 0; // If the node is null, height is 0
        }
        // Get the height of left and right subtrees
        int leftHeight = getHeightHelper(subTreePtr->getLeftChildPtr());
        int rightHeight = getHeightHelper(subTreePtr->getRightChildPtr());
        return ((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1; //+1 for current node
    }

    //helper function to get the total number of nodes recursively
    int getNumberOfNodesHelper(LinkedTreeNode<ItemType>* subTreePtr) const {
        if(subTreePtr == nullptr) {
            return 0; //If empty, number of nodes is 0
        }
        //Recursively call the left and right children
        int leftCount = getNumberOfNodesHelper(subTreePtr->getLeftChildPtr());
        int rightCount = getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
        return leftCount + rightCount + 1; //+1 for root
    }

    //Helper function to clear the tree recursively
    void clearHelper(LinkedTreeNode<ItemType>* subTreePtr) {
        if(subTreePtr != nullptr) {
            //Recursively delete left and right children
            clearHelper(subTreePtr->getLeftChildPtr());
            clearHelper(subTreePtr->getRightChildPtr());
            //Delete the current node
            delete subTreePtr;
        }
    }

    //Helper function to add a new entry to the tree recursively
    LinkedTreeNode<ItemType>* addHelper(const ItemType& newEntry, LinkedTreeNode<ItemType>* subTreePtr) {
        //Base Case
        if(subTreePtr == nullptr) {
            //Create new node and insert new entry
            return new LinkedTreeNode<ItemType>(newEntry);
        }

        //Recursive Add Left if not Right
        //not comparing just left priority as long as not nullptr
        LinkedTreeNode<ItemType>* left = subTreePtr->getLeftChildPtr();
        if (left != nullptr) {
            LinkedTreeNode<ItemType>* newLeft = addHelper(newEntry, left);
            subTreePtr->setLeftChildPtr(newLeft);
        }
        else {
            //If Right Child exists, add to the right side
            LinkedTreeNode<ItemType>* right = subTreePtr->getRightChildPtr();
            if(right != nullptr) {
                LinkedTreeNode<ItemType>* newRight = addHelper(newEntry, right);
                subTreePtr->setRightChildPtr(newRight);
            }
            else {
                //If Both children exist this will keep adding to the left side until nullptr
                LinkedTreeNode<ItemType>* newLeft = addHelper(newEntry, subTreePtr->getLeftChildPtr());
                subTreePtr->setLeftChildPtr(newLeft);
            }
        }
        return subTreePtr;
    }

    //Remove helper function to remove an entry from the tree
    LinkedTreeNode<ItemType>* removeHelper(const ItemType& anEntry, LinkedTreeNode<ItemType>* subTreePtr) {
        //Base case
        if(subTreePtr == nullptr) {
            return subTreePtr; //Subtree is empty
        }

        //If the entry is found, handle different cases
        if(subTreePtr->getItem() == anEntry) {
            //Create pointer to the node to delete to avoid memory leak
            LinkedTreeNode<ItemType>* nodeToDelete = subTreePtr;

            //CASE 1: Node is a leaf (no children)
            if(nodeToDelete->isLeaf()) {
                delete nodeToDelete;
                return nullptr;
            }
            //CASE 2: Only left child
            else if (nodeToDelete->getRightChildPtr() == nullptr) {
                LinkedTreeNode<ItemType>* leftChild = nodeToDelete->getLeftChildPtr();
                delete nodeToDelete;
                return leftChild;
            }
            //CASE 3: Only right child
            else if (nodeToDelete->getLeftChildPtr() == nullptr) {
                LinkedTreeNode<ItemType>* rightChild = nodeToDelete->getRightChildPtr();
                delete nodeToDelete;
                return rightChild;
            }
            //CASE 4: Two children (promote left subtree)
            else {
                //Set new root to left child
                LinkedTreeNode<ItemType>* newRoot = nodeToDelete->getLeftChildPtr();
                //Find rightMost node of promoted left subtree
                LinkedTreeNode<ItemType>* rightMost = newRoot;
                while (rightMost->getRightChildPtr() != nullptr) {
                    rightMost = rightMost->getRightChildPtr();
                }
                //Attach original right subtree
                rightMost->setRightChildPtr(nodeToDelete->getRightChildPtr());
                delete nodeToDelete;
                return newRoot;
            }
        }

        //Recursively search left and right subtrees
        LinkedTreeNode<ItemType>* left = removeHelper(anEntry, subTreePtr->getLeftChildPtr());
        subTreePtr->setLeftChildPtr(left);
        
        LinkedTreeNode<ItemType>* right = removeHelper(anEntry, subTreePtr->getRightChildPtr());
        subTreePtr->setRightChildPtr(right);
        
        return subTreePtr;
    }

    //Function to check if the tree contains a specific entry
    LinkedTreeNode<ItemType>* containsHelper(const ItemType& anEntry, LinkedTreeNode<ItemType>* subTreePtr) const {
        //Base case
        if(subTreePtr == nullptr) {
            return nullptr; //nothing found
        }

        //If the entry VALUE is found, return the node
        if(subTreePtr->getItem() == anEntry) {
            return subTreePtr;
        }

        //Recursively search left and right subtrees
        LinkedTreeNode<ItemType>* foundNode = containsHelper(anEntry, subTreePtr->getLeftChildPtr());
        if(foundNode != nullptr) {
            return foundNode;
        }
        return containsHelper(anEntry, subTreePtr->getRightChildPtr());
    }

public:
    BinaryTree() : rootPtr(nullptr) {}

    virtual bool isEmpty() const override {
        return rootPtr == nullptr;
    }

    //Function to get the longest height of the tree
    virtual int getHeight() const override {
        return getHeightHelper(rootPtr);
    }

    //Gets Total Number of Nodes in the tree
    virtual int getNumberOfNodes() const override {
        return getNumberOfNodesHelper(rootPtr);
    } 

    //This function will return the VALUE of the root node
    virtual ItemType getRootData() const override {
        if(rootPtr == nullptr) {
            throw "Tree is EMPTY";
        }
        return rootPtr->getItem();
    }

    //Function to add a new entry to the tree
    virtual bool add(const ItemType& newEntry) override {
        LinkedTreeNode<ItemType>* newRoot = addHelper(newEntry, rootPtr);
        if (rootPtr == nullptr) {
            rootPtr = newRoot;
        }
        return newRoot != nullptr;
    }

    //Function to remove an entry from the tree
    virtual bool remove(const ItemType& anEntry) override {
        LinkedTreeNode<ItemType>* newRoot = removeHelper(anEntry, rootPtr);
        if (newRoot != rootPtr) {
            rootPtr = newRoot;
        }
        return newRoot != nullptr;
    }

    //Function to clear the entire tree
    virtual void clear() override {
        clearHelper(rootPtr);
        rootPtr = nullptr;
    }

    virtual bool contains(const ItemType& anEntry) const override {
        return containsHelper(anEntry, rootPtr) != nullptr;
    }
};
#endif