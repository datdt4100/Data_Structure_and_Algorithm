#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>
using namespace std;
#ifndef _HASH_
#define _HASH_
class hash {
public:
    int binarySearch(int arr[], int left, int right, int x)
    {
        if (left <= right) {
            if (arr[left + (int)((right - left) / 2)] > x) return binarySearch(arr, left, left + (int)((right - left) / 2) - 1, x);
            else if (arr[left + (int)((right - left) / 2)] < x) return binarySearch(arr, left + (int)((right - left) / 2) + 1, right, x);
            else return left + (int)((right - left) / 2);
        }
        else return -1;
    }

    int sum(pair<int, int> n) {
        return n.first + n.second;
    }

    int C(int k, int n) {
        if (k == 0 || k == n) return 1;
        if (k == 1) return n;
        return C(k - 1, n - 1) + C(k, n - 1);
    }

    bool findPairs(int arr[], int n, pair<int, int>& pair1, pair<int, int>& pair2)
    {
        // TODO: If there are two pairs satisfy the condition, assign their values to pair1, pair2 and return true. Otherwise, return false.
        sort(&arr[0], &arr[n]);
        return 0;
    }

};

#endif // !_HASH_