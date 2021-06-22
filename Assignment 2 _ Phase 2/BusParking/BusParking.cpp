// BusParking.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

#include "BusParking.h"

using namespace std;

class Interval {
public:
    int start;
    int end;

    Interval(int start = 0, int end = 0) {
        this->start = start;
        this->end = end;
    }
};
// SOLUTION
int minPark(vector<Interval> lInterval) {
    int n = lInterval.size();
    if (n == 1) return 1;
    sort(lInterval.begin(), lInterval.end(), [](const Interval A, const Interval B)->bool {if (A.start == B.start) return A.end < B.end; return A.start < B.start; });
    
    vector <int> endValue;
    for (int i = 0; i < n; i++) {
        endValue.push_back(lInterval[i].end);
    }
    sort(endValue.begin(), endValue.end());
    int i = 0;
    int j = 0;
    int result = 1;
    while (true)
    {
        while (j < n && lInterval[i].start >= endValue[j]) {
            j++;
        }
        cout << "j: " << j << "\t";
        if (j == n - 1 || j == n) break;

        while (i < n && lInterval[i].start < endValue[j]) {
            i++;
        }
        cout << "i: " << i << "\t";
        if (i == n - 1 || i == n) break;
        if (i - j > result) result = i - j;
    }
    if (i - j > result) result = i - j;
    return i - j;
}





int _minPark( vector<Interval> lInterval) {
    int n = lInterval.size();
    //if (n == 1 ) return 1;
    sort(lInterval.begin(), lInterval.end(), [](const Interval A, const Interval B)->bool {if (A.start == B.start) return A.end < B.end; return A.start < B.start; });
    for (int i = 0; i < lInterval.size(); i++) {
        cout << setw((wint_t)(lInterval[i].start - lInterval[0].start)) << "";
        cout << lInterval[i].start;
        for (int j = lInterval[i].start; j < lInterval[i].end; j++) {
            cout << "-";
        }
        cout << lInterval[i].end << endl;
    }
    vector <int> endValue;
    for (int i = 0; i < n; i++) {
        endValue.push_back(lInterval[i].end);
    }
    sort(endValue.begin(), endValue.end());
    for (int i = 0; i < n; i++) {
        cout << endValue[i] << "\t";
    }
    cout << endl;
    int count = 0;
    int i = 0;
    int j = 0;
    vector<int> vInterval;
    vInterval.push_back(1);
    int result = 1;
    while (true)
    {
        while (j < n && lInterval[i].start >= endValue[j]) {
            j++;
            count--;
        }
        cout << "j: " << j << "\t";
        if (j == n - 1 || j == n) break;

        while (i < n && lInterval[i].start < endValue[j]) {
            i++;
            count++;
        }
        cout << "i: " << i << "\t";
        if (i == n - 1 || i == n) break;
        if (i - j > result) result = i - j;
    }
    if (i - j > result) result = i - j;
    cout << endl << i << "\t" << j;
    cout << endl;
    
    for (int i = 1; i < lInterval.size(); i++) {
        int less = 0;
        for (int j = 0; j < i; j++) {
            if (lInterval[j].end <= lInterval[i].start)
                less++;
        }
        vInterval.push_back( i + 1 - less);
        cout << vInterval[vInterval.size() - 1] << "\t";
    }
    cout << endl;
    vector<int>::iterator _result = max_element(vInterval.begin(), vInterval.end());
    cout << "kq: " << *_result << "\t" << count << endl;
    return result;

}

int main()
{
    vector<Interval> intervals;
    /*intervals.push_back(Interval(1, 9));
    intervals.push_back(Interval(14, 15));
    intervals.push_back(Interval(9, 14));
    intervals.push_back(Interval(18, 37));
    intervals.push_back(Interval(2, 7));
    intervals.push_back(Interval(5, 11));
    intervals.push_back(Interval(1, 9));
    intervals.push_back(Interval(1, 13));
    intervals.push_back(Interval(15, 18));
    intervals.push_back(Interval(7, 24));
    intervals.push_back(Interval(11, 16));
    intervals.push_back(Interval(2, 16));
    intervals.push_back(Interval(12, 15));
    intervals.push_back(Interval(1, 18));
    intervals.push_back(Interval(18, 34));
    intervals.push_back(Interval(7, 14));
    intervals.push_back(Interval(11, 30));
    intervals.push_back(Interval(9, 22));
    intervals.push_back(Interval(7, 27));
    intervals.push_back(Interval(15, 30));*/
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int tmp = rand() % n;
        intervals.push_back(Interval(tmp, tmp + rand() % n + 1));
        cout << "b->add(" << intervals[i].start << "," << intervals[i].end << ");" << endl;
    }
    /*for (int i = 0; i < intervals.size(); i++) {
        cout << setw((wint_t)(intervals[i].start - 0)) << "";
        cout << intervals[i].start;
        for (int j = intervals[i].start; j < intervals[i].end; j++) {
            cout << "-";
        }
        cout << intervals[i].end << endl;
    }*/
    cout << "\n\n";
    clock_t start, end, time;
    start = clock();
    cout << minPark(intervals) << endl;
    end = clock();
    time = (double)((double)end - (double)start) / CLOCKS_PER_SEC;
    cout << "Runtime: " << time;
    cout << "------\n";
    BusParking* b = new BusParking();
    b->add(1, 9);
    b->add(4, 5);
    b->add(9, 14);
    b->add(8, 17);
    b->add(2, 7);
    b->add(5, 11);
    b->add(1, 9);
    b->add(1, 3);
    b->add(5, 8);
    b->add(7, 14);
    cout << b->minPark();

//    cout << _minPark(intervals);
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
