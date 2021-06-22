
#ifndef _TOY_H_
#include "toy.h"
#define _TOY_H_
#endif


#ifndef FUNCTION_POINTER_H_INCLUDED
#include "function_pointer.h"
#define FUNCTION_POINTER_H_INCLUDED
#endif // FUNCTION_POINTER_H_INCLUDED

#ifndef RECURSIVE_H_INCLUDED
#include "recursive.h"
#define RECURSIVE_H_INCLUDED
#endif

#ifndef _SORT_
#include "sort.h"
#define _SORT_
#endif


#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
#include <math.h>
#include <bits/stdc++.h>

enum ex
{
	disable =0,
	enable = !disable
};

int main(){
    ex a;
    a = enable;
    cout << a;

}

/*
PuzzleToy puzzle1(30000,small);
car1.printType();
puzzle1.printType();

CarToy car2(20000,red);
PuzzleToy puzzle2(30000,small);

ToyBox box;
box.addItem(CarToy car1(20000,red);
car2);
box.addItem(puzzle2);
box.printBox();

Toy* toy = new CarToy(30000,red);
toy->printType();

calculate(1,2,0);
calculate(1,2,1);


int n = 10;
int a[10] = { 4, 6, 1, 3, 4, 7, 8, 9, 10, 0 };
void (*sortAlgorithm)(int[], int) = ascendingSort;

mySort(a, n, sortAlgorithm);
    for (int i = 0; i < n; ++i) {
	printf("%d ", a[i]);
    }

    char s[]="Truong DH Bach Khoa";
    cout<<"lend: "<<strLen(s);
    cout <<"------------"<< endl;
    printPattern(16);
    cout << endl<< dectobi(11)<<endl;
    char num[]="20";
    cout << Arr_to_Int(num,2)<<endl;
    int arr[] = {10, 5, 7, 9, 15, 6, 11, 8, 12, 2};
    cout << findMax(arr, 10);
    cout << endl << isPalindrome("do    geese see god");
    cout << endl << 0%25;

*/


