#ifndef FRAGMENT_LINKED_LIST
#include "FragmentLinkedList.cpp"
#define FRAGMENT_LINKED_LIST
#endif

using namespace std;

int main()
{
    // TESTCASE INPUT
    // === Example
    // for(int i = 0; i < 20 ; i++)
    //     fList.add(i, i * i);
    
    {
        cout << "\n\n---------TEST-01----------\n\n";
        FragmentLinkedList<int> fList;
        for (int i = 0; i < 20; i++)
            fList.add(i * i - 3 * i + 9);
        for (int i = 5; i < 15; i++)
            fList.add(i, 5 * i * i + 7 * i - 27);
        for (int i = 1; i < 5; i++)
            fList.add(0, 10 * i - i * i + 3);
        cout << fList.toString() << "\nSize: " << fList.size() << endl;
        cout << "Remove element at index: " << 0 << "\t data: " << fList.removeAt(0) << endl;
        cout << "Remove element at index: " << fList.size() - 1 << "\t data: ";
        cout << fList.removeAt(fList.size() - 1) << endl;
        cout << "Remove data: ";
        int data = 5 * 5 * 5 + 7 * 5 - 27;
        cout << data << "\tResult: " << fList.removeItem(data) << endl;
        cout << "Remove data: ";
        data = 123456;
        cout << data << "\tResult: " << fList.removeItem(data) << endl;
        cout << "Check empty: " << fList.empty() << "\tSize of List: " << fList.size() << endl;
        cout << "Data at index " << 15 << " :\t" << fList.get(15)<<endl;
        int index = rand() % (fList.size() - 1);
        cout << "Set data at index " << index << " to 2011000" << endl;
        fList.set(index, 2011000);
        cout << "*****" << endl;
        cout << "String list after processing: \n" << fList.toString() << endl;
        fList.clear();
        if (fList.empty()) cout << "List is cleared\n";
        else cout << "List has data: " << fList.toString() << endl;
    }
    {
        cout << "\n\n-----------TEST_02-----------\n\n";
        FragmentLinkedList<float> fList2(2);
        for (int i = 0; i < 5; i++)
            fList2.add(-i * i + 4.9 * i + 20.3);
        cout << "Initial List: ";
        for (FragmentLinkedList<float>::Iterator it = fList2.begin(); it != fList2.end(); it++)
            cout << *it<<" ";
        cout <<"\b"<< endl;

        for (FragmentLinkedList<float>::Iterator it = fList2.begin(1); it != fList2.end(1); it++)
            it.set(123);
        cout << fList2.toString()<<endl;
        for (FragmentLinkedList<float>::Iterator it = fList2.begin(); it != fList2.end(); it++)
            it.remove();
        for (FragmentLinkedList<float>::Iterator it = fList2.begin(); it != fList2.end(); it++)
            cout << *it << " ";
        cout << "\b" << endl;
        cout << fList2.toString();
    }

    /*cout<< "numNode: "<<fList.size()<<"\t num frag: "<<fList.getF()<<"\t remove: "<< fList.removeItem(9)<<endl;
    cout <<"List: "<< fList.toString()<<"\n frag: ";
    fList.displayfList();
    cout <<endl<< "Get:\t"<<fList.get(3)<<endl;
    fList.clear();
    cout <<endl<< "Get:\t"<<fList.get(3)<<endl;
    cout<<fList.empty();
    cout<< "numNode: "<<fList.size()<<"\t num frag: "<<fList.getF();
    fList.displayfList();
    cout << fList.toString()<<endl;
    //fList.displayfList();*/
    /*
    cout << "xoa: " << fList.removeItem(64) << "\nchuoi:\t" << fList.toString() << endl;
    cout << endl << "remove: " << fList.removeAt(2) << " and " << fList.removeAt(0) << " and " << fList.removeAt(0) << endl;
    cout << fList.toString() << endl << "vi tri 5 la: " << fList.get(5) << endl;
    fList.set(6,12345);
    cout <<"List: "<<fList.toString()<<endl;
    int l;
    do {
        cout << "Check find index of: ";
        cin >> l;
        if (!cin.good()){
            cin.clear();
            cin.ignore(0xfffffff,'\0');
        }
        cout <<"Find index of: "<<l<<"\t"<<fList.indexOf(l)<<endl;
        cin.clear();
    }while (l != 000);

    do {
        cout << "Check element: ";
        cin >> l;
        if (!cin.good()){
            cin.clear();
            cin.ignore(0xfffffff,'\0');
        }
        cout <<"Contains?: "<<"\t"<<fList.contains(l)<<endl;
        cin.clear();
    }while (l != 000);

    cout << "-------------" << endl;
    cout << fList.toString() << endl;
    cout << "numNode: " << fList.size() << endl << "num frag: " << fList.getnumF() << endl;
    cout << "--------------------------" << endl;
    for (FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.end(); it++) {
        if (*it == 12345) it.remove();
        else cout << *it << " ";
    }
    cout << endl << fList.toString() << endl;
    cout << "numNode: " << fList.size() << endl << "num frag: " << fList.getnumF() << endl;
    for (int i = 0; i < fList.getnumF(); i++) {
        cout << fList.getdataF(i) << "-----";
    }

    // cout << endl;
    // === END: Example
    // END: TESTCASE INPUT*/

    FragmentLinkedList<int> fList;
    for (int i = 0; i < 10; i++) fList.add(i);
    for (int i = 0; i < 20; i++)
        fList.add(i, i * i);
    fList.toString();
    fList.size();
    fList.empty();
    fList.contains(1);
    fList.removeAt(1);
    fList.indexOf(5);
    fList.removeItem(5);
    fList.set(1, 10000);
    fList.toString();
    for (FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.end(); it++)
    {
        if (*it % 5 == 0) {
            *it = 1000;
        }
        else if (*it % 3 == 0) {
            it.remove();
        }
        else if (*it % 10 == 0) it.set(1000000);

    }
// cout << endl;
// === END: Example
// END: TESTCASE INPUT

    return 0;
}

