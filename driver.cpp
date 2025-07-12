//Carla Embuido
//7-8-2025
//Purpose: Implementation of the driver for the binary tree

#include <iostream>
#include <cstdlib>
#include "binarysearchtree.h"
using namespace std;
int main(){

    //Intialize random seed
    srand(time(0));

    //initialize a Binary Search Tree
    BinarySearchTree<int> BST;

    //Generate 100 UNIQUE values range 1-200
    for (int i = 0; i < 100; i++){
        int randomValue = rand() % 200 + 1;
        //ADD the value to the BST
        BST.add(randomValue);
    }

    //Displau Properties
    cout << "Height of Tree: " << BST.getHeight() << endl;

    //Display the DIFFERENT transversals
    cout << "Inorder Traversal: ";
    BST.inorderTraversal();

    cout << "Preorder Traversal: ";
    BST.preorderTraversal();

    cout << "Postorder Traversal: ";
    BST.postorderTraversal();

    return 0;
}