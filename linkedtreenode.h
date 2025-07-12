//This contains AND HOLDS NODE DATA to be used in other tree implementations (#include
#ifndef TREE_NODE 
#define TREE_NODE

template<class ItemType> 
class LinkedTreeNode{ 
private: 
    ItemType item;  
    LinkedTreeNode<ItemType>* leftChildPtr;  
    LinkedTreeNode<ItemType>* rightChildPtr; 
public: 
    LinkedTreeNode();
    LinkedTreeNode(const ItemType& newData);
    LinkedTreeNode(const ItemType& newData, LinkedTreeNode<ItemType>* left, LinkedTreeNode<ItemType>* right);

    bool isLeaf() const;

    ItemType getItem() const;
    LinkedTreeNode<ItemType>* getLeftChildPtr() const;
    LinkedTreeNode<ItemType>* getRightChildPtr() const;

    //Setters to change the node's data and pointers
    void setItem(const ItemType& newData);

    //Attach or detach left and right children IT POINTS TO STUFF
    //POINTS PARENTS TO CHILDREN
    void setLeftChildPtr(LinkedTreeNode<ItemType>* newLeftChildPtr);
    void setRightChildPtr(LinkedTreeNode<ItemType>* newRightChildPtr);
};
#include "linkedtreenode.cpp"
#endif
