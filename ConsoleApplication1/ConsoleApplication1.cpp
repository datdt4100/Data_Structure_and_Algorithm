// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#ifndef _SORT_
#include "sort.h"
#define _SORT_
#endif

#ifndef _STACK_QUEUE_
#include "Stack_Queue.h"
#define _STACK_QUEUE_
#endif

#ifndef _HASH_
#include "hash.h"
#define _HASH_
#endif

#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int main()
{
    Hash check;
    int arr[] = { 3, 4, 7, 1, 2, 9, 8 };
    int n = sizeof arr / sizeof arr[0];
    pair<int, int> pair1, pair2;
    cout << check.findPairs(arr, n, pair1, pair2);
}

/*
int main()
{
    
    Stack<int> nStack;
    int* arr = new int[10];
    for (int i = 0; i < 10; i++) {
        arr[i] = 5 * i + 3;
        nStack.push(arr[i]);
    }
    cout << "INITIAL ARRAY:\n";
    for (int i = 0; i < 10; i++){
        cout << arr[i] << "\t";
    }
    cout << "ARRAY IN STACK:\n";
    nStack.show();
    cout << "------------------\n";
    for (int i = 0; i < 10; i++) {
        arr[i] = nStack.top();
        nStack.pop();
    }
    cout << endl << endl << "AFTER CHANGE:\n";
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << "\t";
    }
    ///////////////////////////////////////
    std::cout << "Hello World!\n";
    int num_segment_list[] = { 1, 3, 5 };
    int num_phases = 3;

    int n = 10;
    int* a = new int[n];
    for (int i = 0; i < n; i++) a[i] = rand() % 100;
    Sort<int> Arr(a, n);
    Sort<int> Arr1(a, n);
    Arr.ShowArr();
    cout << "\n";
    clock_t bt = clock(), et;
    cout << "-------" << endl;
    Arr.mergeSort(&a[0], &a[n-1]);
    Arr.ShowArr();
    et = clock();
    cout << "\n";
    cout << "Runtime: " << (float)(et - bt) / CLOCKS_PER_SEC<<endl;
    cout << "*********************\n";
    int arr[] = {4, 9, 2, 8, 4, 1 };
    SLinkedList<int> list;
    for (int i = 0; i <int(sizeof(arr)) / 4; i++)
        list.add(arr[i]);
    list.bubbleSort();
    list.printList();
    
}
*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
