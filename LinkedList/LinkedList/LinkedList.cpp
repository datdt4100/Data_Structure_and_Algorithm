// LinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "LinkedList.h"

int main(int argv, char** argc){
    DoubleLList<int> *ls = new DoubleLList<int>();
    for (int i = 0; i < 10; i++) {
        ls->add(i * i);
    }
    ls->show();
    ls->removeAt(3);
    
    for (int i = 3; i < 6; i++) {
        ls->removeAt(i);
        cout << i << endl;
    }
    ls->removeValue(81);
    ls->show();
    ls->clear();
    ls->show();
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
