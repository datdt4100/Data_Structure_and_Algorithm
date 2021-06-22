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
class Hash {
public:
    static int binarySearch(int arr[], int left, int right, int x)
    {
        if (left <= right) {
            if (arr[left + (int)((right - left) / 2)] > x) return binarySearch(arr, left, left + (int)((right - left) / 2) - 1, x);
            else if (arr[left + (int)((right - left) / 2)] < x) return binarySearch(arr, left + (int)((right - left) / 2) + 1, right, x);
            else return left + (int)((right - left) / 2);
        }
        else return -1;
    }

    static int sum(pair<int, int> n) {
        return n.first + n.second;
    }

    static int C(int k, int n) {
        if (k == 0 || k == n) return 1;
        if (k == 1) return n;
        return C(k - 1, n - 1) + C(k, n - 1);
    }

    static bool findPairs(int arr[], int n, pair<int, int>& pair1, pair<int, int>& pair2)
    {
        // TODO: If there are two pairs satisfy the condition, assign their values to pair1, pair2 and return true. Otherwise, return false.
        if (n < 4) return 0;
        sort(&arr[0], &arr[n]);
        for (int i = 0; i < n; i++) {
            cout << arr[i] << "\t";
        }
        cout << "\n-------------\n";
        for (int i = 0; i < n - 3; i++) {
            int tmp = 0;
            while (arr[i] + arr[n - 1] <= arr[n - 2] + arr[tmp]) {
                if (tmp == i) tmp++;
                if (arr[i] + arr[n - 1] == arr[n - 2] + arr[tmp]) {
                    pair1.first = arr[i];
                    pair1.second = arr[n - 1];
                    pair2.first = arr[n - 2];
                    pair2.second = arr[tmp];
                    return 1;
                }
                tmp++;
            }
        }
        return 0;
    }

};

#endif // !_HASH_