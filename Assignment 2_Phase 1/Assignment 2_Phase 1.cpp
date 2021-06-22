// Assignment 2_Phase 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef _BKUTree_
#include "BKUTree.h"
#define _BKUTree_
#endif // !_BKUTree_
template<class K, class V>
void printKey(K key, V value) {
    cout << key << " ";
}

int main()
{
    try {
        vector<int> traversedlist;
        BKUTree<int, int>* tree = new BKUTree<int, int>(8);
        int keys[] = { 25,73,89,23,14,53,25,55,17,16,21,90,6,54,12,60,8,86,18,69,100,0,70,77,65,22 };
        for (int i = 0; i < 26; i++) {
            tree->add(keys[i], i * 2 + keys[i] - 7);
        }
        cout << "----";
        tree->remove(6);
        tree->remove(54);
        tree->remove(21);
        tree->traverseNLROnAVL(printKey);
        cout << endl;
        tree->traverseNLROnSplay(printKey);
        cout << endl;
        cout << tree->search(53, traversedlist) << endl;
        cout << tree->search(73, traversedlist) << endl;
        cout << tree->search(14, traversedlist) << endl;
        for (int i = 0; i < (int)traversedlist.size(); i++) {
            cout << traversedlist[i] << "  ";
        }
        cout << endl;
        tree->traverseNLROnAVL(printKey);
        cout << endl;
        tree->traverseNLROnSplay(printKey);
        delete tree;
    }
    catch (const char* exception) {
        cout << exception;
    }
    return 0;
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
