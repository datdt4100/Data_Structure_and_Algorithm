#include <iostream>
using namespace std;

#ifndef _SORT_
#define _SORT_



class Sort
{
private:
	int *arr;
	int nlength;
public:
	Sort(): arr(nullptr), nlength(0) {};
	Sort(int arr[], int nlength){
		this->arr = arr;
		this->nlength = nlength;
	}
	~Sort () {delete arr; arr = nullptr;}
	void ShowArr();
	void InsertionSort();
};

void Sort::ShowArr()
{
	for (int i=0; i< nlength; i++){
		cout << arr[i] << "\t";
	}
}

void Sort::InsertionSort()
{
	if (nlength > 1){
		int j = 1;
		while (j < nlength){
			
			int index = j-1;
			int tmp = arr[j];
			while (index >= 0 && arr[index] > tmp){
				arr[index+1] = arr[index];
				index --;
			}
			arr[index] = tmp;
			j++;
		}
	}
}


#endif