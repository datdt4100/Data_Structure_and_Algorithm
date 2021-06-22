#include "Lib.h"
#ifndef _Sort_h_
#define _Sort_h_

template <class T>
class Sort {
	T* arr;
	int size;
public:
	Sort(T*, int) ;
	void InsertionSort() ;
	
	void ShellSort(int* segment_list, int numPhase); // segment_list = [1, 5, 9], numphase = 3;
	void SegmentSort(int nth_segment, int increase_value);
	
	void SelectionSort();

	void HeapSort();
	void ReHeapDown(int, int);
	void ReHeapUp(int, int);

	void BubbleSort();

	void QuickSort(int, int);
	int getPartition(int, int);
	int getPartitionAtHead(int, int);

	void Show() ;
	void ShowLimit(int, int);
	void Swap(T&, T&);

};

template<class T>
Sort<T>::Sort(T* arr, int size) {
	this->arr = arr;
	this->size = size;
}

template<class T>
void Sort<T>::Show() {
	for (int i = 0; i < this->size; i++) {
		cout << arr[i] << "\t";
	}
	cout << endl;
}

template <class T>
void Sort<T>::ShowLimit(int s, int e) {
	for (; s < e; s++) {
		cout << arr[s] << " ";
	}
	cout << endl;
}

template <class T>
void Sort<T>::Swap(T& dataA, T& dataB) {
	T tmp = dataA;
	dataA = dataB;
	dataB = tmp;
}

template<class T>
void Sort<T>::InsertionSort() {
	if (size > 1) {
		int i = 1;
		while (i < this->size) {
			int idx = i;
			T tmp = arr[i];
			while (idx > 0 && arr[idx-1] > tmp) {
				arr[idx] = arr[idx - 1];
				idx--;
			}
			arr[idx] = tmp;
			i++;
		}
	}
}

template<class T>
void Sort<T>::SegmentSort(int nth_segment, int increase_value) {
	// like Insertion Sort
	int initial_idx = nth_segment + increase_value; // index 1 in general
	while (initial_idx < this->size) {
		T temp_data = this->arr[initial_idx];
		int idx = initial_idx - 1;
		while (idx > -1 && arr[idx] > temp_data) {
			this->arr[idx + 1] = this->arr[idx];
			idx--;
		}
		this->arr[idx + 1] = temp_data;
		initial_idx += increase_value;
	}
}

template <class T>
void Sort<T>::ShellSort(int* segment_list, int numphase) {
	while (numphase > 0) {
		numphase--;
		int nth_segment = 0;
		while (nth_segment < segment_list[numphase]) {
			this->SegmentSort(nth_segment, segment_list[numphase]);
			nth_segment++;
		}
	}
}

template <class T>
void Sort<T>::SelectionSort() {
	for (int i = 0; i < this->size; i++) {
		int idx = i + 1;
		int small_pos = i;
		while (idx < this->size) {
			if (arr[idx] < arr[small_pos]) small_pos = idx;
			idx++;
		}
		T tmp = arr[i];
		arr[i] = arr[small_pos];
		arr[small_pos] = tmp;
	}
}

template <class T>
void Sort<T>::HeapSort() {
	int last_parent = this->size / 2 - 1;
	while (last_parent > -1) {
		ReHeapDown(last_parent, this->size);
		last_parent--;
	}
	int last_sorted_idx = this->size - 1;
	while (last_sorted_idx > 0) {
		Swap(arr[0], arr[last_sorted_idx]);
		
		ReHeapDown(0, last_sorted_idx);
		last_sorted_idx--;
	}
}

template <class T>
void Sort<T>::ReHeapUp(int old_root, int num_element) {
	int left_child = old_root * 2 + 1;
	int right_child = old_root * 2 + 2;
	int new_root = old_root;
	if (left_child < num_element && arr[new_root] < arr[left_child])
		new_root = left_child;
	if (right_child < num_element && arr[new_root] < arr[right_child])
		new_root = right_child;
	if (new_root != old_root) {
		Swap(arr[new_root], arr[old_root]);
		ReHeapUp(new_root, num_element);
	}
}

template <class T>
void Sort<T>::ReHeapDown(int old_root, int num_element) {
	int left_child = old_root * 2 + 1;
	int right_child = old_root * 2 + 2;
	int new_root = old_root;
	if (left_child < num_element && arr[new_root] > arr[left_child])
		new_root = left_child;
	if (right_child < num_element && arr[new_root] > arr[right_child])
		new_root = right_child;
	if (new_root != old_root) {
		Swap(arr[new_root], arr[old_root]);
		ReHeapDown(new_root, num_element);
	}
}

template <class T>
void Sort<T>::BubbleSort() {
	int i = 0;
	bool finished = 1;
	while (i < this->size && finished) {
		int idx = this->size - 1;
		finished = 0;
		while (idx > i) {
			if (arr[idx] < arr[idx - 1]) {
				Swap(arr[idx], arr[idx - 1]);
				finished = 1;
			}
			idx--;
		}
		i++;
	}
}

template <class T>
void Sort<T>::QuickSort(int left_idx, int right_idx) {
	if (left_idx < right_idx) {
		int pivot = getPartitionAtHead(left_idx, right_idx);
		QuickSort(left_idx, pivot - 1);
		QuickSort(pivot + 1, right_idx);
	}
}

template <class T>
int Sort<T>::getPartition(int left_idx, int right_idx) {
	T Partition_value = arr[right_idx];
	left_idx--;

	for (int i = left_idx + 1; i < right_idx; i++) {
		if (arr[i] < Partition_value) {
			left_idx++;
			Swap(arr[left_idx], arr[i]);
		}
	}
	left_idx++;
	Swap(arr[left_idx], arr[right_idx]);
	return left_idx;
}

template <class T>
int Sort<T>::getPartitionAtHead(int left_idx, int right_idx) {
	int left_margin = left_idx + 1;
	int right_margin = right_idx;
	T* ParVal = &arr[left_idx];
	left_idx++;
	while (true) {
		Show();
		while (left_idx < right_margin && arr[left_idx] < *ParVal) left_idx++;
		while (right_idx > left_margin && arr[right_idx] >= *ParVal) right_idx--;
		if (left_idx >= right_idx) break;
		Swap(arr[left_idx], arr[right_idx]);
	}
	Swap(arr[right_idx], *ParVal);
	return right_idx;
}
#endif
