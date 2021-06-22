// SortAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "SORT.h"
#include "Lib.h"

int main()
{
	int size = 10;
	int* arr = new int[size];
	for (int i = 0; i < size; i++) arr[i] = rand() % 100;
	int array[] = { 30, 7, 20, 0, -13, 1, 19, 72 };
	Sort<int> ls(array, 8);

	ls.Show();
	ls.QuickSort(0, 7);
	ls.Show();
	return EXIT_SUCCESS;
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
