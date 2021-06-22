// BinarySearchTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

#ifndef _BST_
#include "BST.h"
#define _BST_
#endif

#ifndef _AVL_
#include "AVL.h"
#define _AVL_
#endif

#ifndef _SPLAY_
#include "Splay.h"
#define _SPLAY_
#endif

template<class K, class V>
void printKey(K key, V value) {
    cout << key << " ";
}

int main()
{
    try
    {
        AVLTree<int>* tree = new AVLTree<int>();
        int keys[] = { 36, 25, 4, 15, 12, 19, 3, 8, 17, 6, 20 };
        for (int i = 0; i < 11; i++) {
            tree->insert(keys[i]);
        }
        
        tree->printTreeStructure();
        cout << "\n----------\n";
        tree->remove(4);
        tree->printTreeStructure();
    }
    catch (const char* msg) {
        cout << msg;
    }
    

    //std::cout << "Hello World!\n";
    // BinaryTree<int, int> bst;
    /*
    bst.addNode("", 1, 12);
    bst.addNode("L", 2, 6);
    bst.addNode("LL", 3, 4);
    bst.addNode("LLL", 4, 2);
    bst.addNode("LLR", 5, 5);
    bst.addNode("LLLR", 6, 3);
    bst.addNode("LLLL", 7, 1);
    bst.addNode("R", 8, 13);
    bst.addNode("LR", 9, 10);
    bst.addNode("LRL", 10, 8);
    bst.addNode("LRLL", 11, 7);
    bst.addNode("LRLR", 12, 9);
    bst.addNode("LRR", 13, 11);
    cout << bst.getDiameter() << endl;
    bst.BFS();
    cout << endl;
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4); // Add to root
    binaryTree.addNode("L", 3, 2); // Add to root's left node
    binaryTree.addNode("R", 5, 10); // Add to root's right node
    binaryTree.BFS();
    cout << endl;
    cout << binaryTree.countTwoChildrenNode();
    cout << binaryTree.isBST();
    cout << binaryTree.getHeight();
    cout << endl << "----------" << endl;
    BinarySearchTree<int> bst1;
    for (int i = 0; i < 10; ++i) {
        bst1.add(i);
    }
    
    cout << bst1.find(7) << endl;
    cout << bst1.sum(0, 4) << endl;
    */

    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
