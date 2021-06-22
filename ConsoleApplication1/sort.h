#include <iostream>
#include <sstream>
using namespace std;

#ifndef _SORT_
#define _SORT_


template<class T>
class Sort
{
private:
	T *arr;
	int nlength;

	static void printArray(T* start, T* end)
	{
		long size = end - start + 1;
		for (int i = 0; i < size - 1; i++)
			cout << start[i] << ", ";
		cout << start[size - 1];
		cout << endl;
	}

	static void sortSegment(T* start, T* end, int segment_idx, int cur_segment_total);
public:
	Sort(): arr(nullptr), nlength(0) {};
	Sort(T *arr, int nlength){
		this->arr = arr;
		this->nlength = nlength;
	}
	~Sort() {
		if (!arr) {
			delete [] arr;
			arr = nullptr;
		}
	}
	void Swap(T& valA, T& valB) {
		T tmp = valA;
		valA = valB;
		valB = tmp;
	}
	void ShowArr();
	void InsertionSort();
	void SelectionSort();
	void BubbleSort();
	static void ShellSort(T* start, T* end, int* num_segment_list, int num_phases);
	void ReheapDown(int pos, int nlength);
	void HeapSort();
	static void merge(T* left, T* middle, T* right);
	static void mergeSort(T* start, T* end);
	void QuickSort();
	void QuickSortRecursive(int left, int right);
	int Partition(int left, int right);
};

template<class T>
void Sort<T>::ShowArr()
{
	for (int i=0; i< nlength; i++){
		cout << arr[i] << "\t";
	}
}

template<class T>
void Sort<T>::InsertionSort()
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
			arr[index + 1] = tmp;
			j++;
		}
	}
}

template<class T>
void Sort<T>::SelectionSort()
{
	if (nlength > 1) {
		int j = 0;
		while (j < (nlength - 1)) {
			int small = j;
			int tmp = j + 1;
			while (tmp < nlength) {
				if (arr[tmp] < arr[small])
					small = tmp;
				tmp++;
			}
			if (small != j) {
				arr[small] += arr[j];
				arr[j] = arr[small] - arr[j];
				arr[small] = arr[small] - arr[j];
			}
			j++;
		}
	}
}

template <class T>
void Sort<T>::BubbleSort()
{
	bool change = 0;
	int i = 0;
	while (i<nlength && change != 1 )
	{
		change = 1;
		int j = nlength - 1;
		while (j > i) {
			if (arr[j] < arr[j - 1]) {
				arr[j] = arr[j - 1] + arr[j];
				arr[j - 1] = arr[j] - arr[j - 1];
				arr[j] = arr[j] - arr[j - 1];
				change = 0;
			}
			j--;
		}
		i++;
	}
}

template<class T>
void Sort<T>::sortSegment(T* start, T* end, int segment_idx, int cur_segment_total) {
	int size = end - start;
	int n = segment_idx;
	while (n + cur_segment_total < size) {
		T tmp = start[n + cur_segment_total];
		int k = n - segment_idx + cur_segment_total;
		while (k >= 0 && start[k] > tmp) {
			start[k + segment_idx] = start[k];
			k -= segment_idx;
		}
		start[k + segment_idx] = tmp;
		n += segment_idx;
	}
	/*
	if (size > 1) {
		int j = segment_idx + cur_segment_total;
		while (j < size) {

			int index = j - segment_idx;
			T tmp = start[j];
			while (index >= 0 && start[index] > tmp) {
				start[index + segment_idx] = start[index];
				index -= segment_idx;
			}
			start[index + segment_idx] = tmp;
			j += segment_idx;
		}
	}*/
}
template<class T>
void Sort<T>::ShellSort(T* start, T* end, int* num_segment_list, int num_phases) {
	while (num_phases > 0) {
		int segment_count = 0;
		while (segment_count < num_segment_list[num_phases - 1]) {
			sortSegment(start, end, num_segment_list[num_phases - 1], segment_count);
			segment_count++;
		}
		num_phases--;
	}
}



template<class T>
void Sort<T>::ReheapDown(int pos, int nlength) {
	int max_pos = pos;
	if ((pos * 2 + 1) < nlength && this->arr[pos * 2 + 1] > this->arr[max_pos]) {
		max_pos = pos * 2 + 1;
	}
	if ((pos * 2 + 2) < nlength && this->arr[pos * 2 + 2] > this->arr[max_pos]) {
		max_pos = pos * 2 + 2;
	}
	if (max_pos != pos) {
		this->Swap(this->arr[max_pos], this->arr[pos]);
		ReheapDown(max_pos, nlength);
	}
}

template <class T>
void Sort<T>::HeapSort() {
	int pos = (this->nlength / 2) - 1;
	while (pos >= 0) {
		ReheapDown(pos, this->nlength);
		pos--;
	}
	pos = nlength - 1;
	while (pos >= 0) {
		this->Swap(this->arr[0], this->arr[pos]);
		ReheapDown(0, pos);
		pos--;
	}
}

template<class T>
void Sort<T>::merge(T* left, T* middle, T* right) {
	/*T* tmparr1 = new T[middle - left + 1];
	T* tmparr2 = new T[right - middle];
	for (int i = 0; i < (middle - left + 1); i++) {
		tmparr1[i] = left[i];
	}
	for (int i = 0; i < (right - middle); i++) {
		tmparr2[i] = middle[i + 1];
	}
	int k = 0;
	int i = 0;
	int j = 0;
	while (i < (middle - left + 1) && j < (right - middle)) {
		if (tmparr1[i] < tmparr2[j]) {
			left[k] = tmparr1[i];
			i++;
		}
		else {
			left[k] = tmparr2[j];
			j++;
		}
		k++;
	}

	while (i < (middle - left + 1)) {
		left[k] = tmparr1[i];
		i++;
		k++;
	}

	while (j < (right - middle)) {
		left[k] = tmparr2[j];
		j++;
		k++;
	}
	delete[] tmparr1;
	delete[] tmparr2;*/
	T* tmpL = left;
	T* tmpM = middle;
	T* tmpR = right;
	tmpM++;
	T* tmpArr = new T[right - left + 1];
	while (tmpL != (middle+1) && tmpM != (right+1)) {
		if (*tmpL < *tmpM) {
			*tmpArr = *tmpL;
			tmpL++;
		}
		else {
			*tmpArr = *tmpM;
			tmpM++;
		}
		tmpArr++;
	}
	while (tmpL != (middle+1)) {
		*tmpArr = *tmpL;
		tmpArr++;
		tmpL++;
	}
	while (tmpM != (right+1)) {
		*tmpArr = *tmpM;
		tmpArr++;
		tmpM++;
	}
	tmpArr--;
	while (tmpR != (left-1)) {
		*tmpR = *tmpArr;
		tmpArr--;
		tmpR--;
	}
	tmpArr++;
	delete[] tmpArr;
	Sort<T>::printArray(left, right);
}

template<class T>
void Sort<T>::mergeSort(T* start, T* end) {
	if (end > start) {
		T* tmp = start + (int)((end - start) / 2);
		mergeSort(start, tmp);
		mergeSort(tmp + 1, end);
		merge(start, tmp, end);
	}
}

template <class T>
int Sort<T>::Partition(int left, int right) {
	int pivot = arr[right];
	int tmp = right;
	right--;
	while (1) {
		while (left <= right && arr[left] < pivot) left++;
		while (right >= left && arr[right] > pivot) right--;
		if (left >= right) break;
		Swap(arr[left], arr[right]);
		left++;
		right--;
	}
	Swap(arr[left], arr[tmp]);
	return left;
}

template<class T>
void Sort<T>::QuickSortRecursive(int left, int right) {
	if (left < right) {
		int pivot_pos = Partition(left, right);
		QuickSortRecursive(left, pivot_pos - 1);
		QuickSortRecursive(pivot_pos + 1, right);
	}
}

template<class T>
void Sort<T>::QuickSort() {
	QuickSortRecursive(0, nlength - 1);
}


template <class T>
class SLinkedList {
public:
	class Node; // Forward declaration
protected:
	Node* head;
	Node* tail;
	int count;
public:
	SLinkedList()
	{
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}
	~SLinkedList() {};
	void add(T e)
	{
		Node* pNew = new Node(e);

		if (this->count == 0)
		{
			this->head = this->tail = pNew;
		}
		else
		{
			this->tail->next = pNew;
			this->tail = pNew;
		}

		this->count++;
	}
	int size()
	{
		return this->count;
	}
	void printList()
	{
		stringstream ss;
		ss << "[";
		Node* ptr = head;
		while (ptr != tail)
		{
			ss << ptr->data << ",";
			ptr = ptr->next;
		}

		if (count > 0)
			ss << ptr->data << "]";
		else
			ss << "]";
		cout << ss.str() << endl;
	}
public:
	class Node {
	private:
		T data;
		Node* next;
		friend class SLinkedList<T>;
	public:
		Node() {
			next = 0;
		}
		Node(T data) {
			this->data = data;
			this->next = nullptr;
		}
	};

	void bubbleSort() {
		bool check_change = 1;
		int i = 0;
		Node* checked = tail->next;
		while (i < this->count && check_change != 0) {
			check_change = 0;
			Node* tmpCheck = head;
			while (tmpCheck->next != checked) {
				if (tmpCheck->data > tmpCheck->next->data) {
					T tmpData = tmpCheck->data;
					tmpCheck->data = tmpCheck->next->data;
					tmpCheck->next->data = tmpData;
					check_change = 1;
				}
				tmpCheck = tmpCheck->next;
			}
			checked = tmpCheck;
			i++;
		}
	}
};



#endif