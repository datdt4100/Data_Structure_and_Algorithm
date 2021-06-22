#ifndef FRAGMENT_LINKED_LIST
#include "FragmentLinkedList.cpp"
#define FRAGMENT_LINKED_LIST
#endif

int main()
{
    // TESTCASE INPUT
    // === Example
    // for(int i = 0; i < 20 ; i++)
    //     fList.add(i, i * i);

    FragmentLinkedList<int> fList;
    for (int i=0;i<20;i++)
        fList.add(i,i*i-3*i+9);
    for (int i=5; i < 15 ; i++)
         fList.add(i, 5*i*i+7*i-27);
        cout<<fList.toString();
        cout<< "numNode: "<<fList.size()<<endl<<"num frag: "<<fList.getF()<<endl;
		for(int i = 1; i < 5 ; i++)
         fList.add(0,10*i-i*i+3);

        /*
		cout << fList.toString()<<endl;
		cout<< "numNode: "<<fList.size()<<"\t num frag: "<<fList.getF()<<"\t remove: "<< fList.removeItem(9)<<endl;
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

        cout <<"xoa: "<<fList.removeItem(64)<<"\nchuoi:\t"<< fList.toString()<<endl;
		cout << endl<<"remove: "<<fList.removeAt(2)<<" and "<<fList.removeAt(0)<<" and "<<fList.removeAt(0)<<endl;
  		cout << fList.toString()<<endl<<"vi tri 5 la: "<<fList.get(5)<<endl;
  		/*fList.set(6,12345);
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


*/

    cout <<"-------------"<<endl;
    cout<<fList.toString()<<endl;
    cout<< "numNode: "<<fList.size()<<endl<<"num frag: "<<fList.getF()<<endl;
    cout <<"--------------------------"<<endl;
    for(FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.end(); it++){
            if (*it == 12345) it.remove();
            else cout << *it << " ";
    }
    cout<<endl<<fList.toString()<<endl;
    cout<< "numNode: "<<fList.size()<<endl<<"num frag: "<<fList.getF()<<endl;
    for (int i=0;i < fList.getF(); i++){
            cout << fList.getdataF(i)<<"-----";
		}

    // cout << endl;
    // === END: Example
    // END: TESTCASE INPUT

    return 0;
}

