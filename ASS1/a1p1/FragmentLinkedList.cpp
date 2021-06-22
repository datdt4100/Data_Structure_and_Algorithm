#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
using namespace std;

#ifndef ILIST_H
#define ILIST_H

template <class T>
class IList
{
public:
    virtual void add(const T& element) = 0;
    virtual void add(int index, const T& element) = 0;
    virtual T removeAt(int index) = 0;
    virtual bool removeItem(const T& item) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T get(int index) = 0;
    virtual void set(int index, const T& element) = 0;
    virtual int indexOf(const T& item) = 0;
    virtual bool contains(const T& item) = 0;
    virtual string toString() = 0;
};

#endif

// STUDENT ANSWER
#ifndef FRAGMENT_LINKED_LIST
#define FRAGMENT_LINKED_LIST
template <class T>
class FragmentLinkedList : IList<T>
{
public:
    class Node;
    class Iterator;

protected:
    Node **fragmentPointers;
    int fragmentMaxSize;
    int count;
    int numfrag; // ADD---------------------------------------

public:
    FragmentLinkedList(int fragmentMaxSize = 5)
    {
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->fragmentPointers = new Node *[2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
        this->numfrag = 2;
    }
    virtual ~FragmentLinkedList()
    {
        for (int i=0; i< numfrag;i++){
            delete [] fragmentPointers[i];
            fragmentPointers[i]= nullptr;
        }
        delete [] fragmentPointers;
        fragmentPointers = nullptr;
    }
    int getF(){return this->numfrag;}
    T getdataF(int index){ return this->fragmentPointers[index]->data;}

    virtual void setFragment()
    {

        Node *tmp = fragmentPointers[0];
        fragmentPointers = new Node*[this->numfrag];
        for (int j=0; j < this->numfrag-1; j++){
            fragmentPointers[j] = tmp;
            int tmpcount = this->fragmentMaxSize;
            while(tmpcount && tmp->next != nullptr){
                tmpcount--;
                tmp = tmp->next;
            }
        }
        fragmentPointers[this->numfrag-1]= tmp;
    }
    virtual void add(const T& element);
    virtual void add(int index, const T& element);
    virtual T removeAt(int index);
    virtual bool removeItem(const T& item);
    virtual bool empty(){return (!this->count)? 1:0;}
    virtual int size(){return this->count;}
    virtual void clear();
    virtual T get(int index);
    virtual void set(int index, const T& element);
    virtual int indexOf(const T& item);
    virtual bool contains(const T& item);
    virtual string toString();
    virtual void displayfList();
    Iterator begin(int index = 0)
    {
        Iterator tmp(index,this,1);
        return tmp;
    }
    Iterator end(int index = -1)
    {
        if (index == -1){
            Iterator tmp(this,0);
            return tmp;
        } else {
            Iterator tmp(index, this, 0);
            return tmp;
        }
    }

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *prev;
        friend class FragmentLinkedList<T>;

    public:
        Node()
        {
            next = 0;
            prev = 0;
        }
        Node(Node *next, Node *prev)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node *next, Node *prev)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    class Iterator
    {
    private:
        FragmentLinkedList<T> *pList;
        Node *pNode;
        int index;

    public:
        Iterator(FragmentLinkedList<T> *pList = 0, bool begin = true)
        {
            this->pList = pList;
            if (begin) {
                pNode= this->pList->fragmentPointers[0];
                index = 0;
            } else {
                pNode = nullptr;
                index = pList->size();
            }
        }
        Iterator(int fragmentIndex, FragmentLinkedList<T> *pList = 0,  bool begin = true)
        {
            if (fragmentIndex < 0 || fragmentIndex >= pList->getF())
                throw std::out_of_range("Segmentation fault!");
            this->pList = pList;
            if (begin){
                pNode = this->pList->fragmentPointers[fragmentIndex];
                index = this->pList->fragmentMaxSize*fragmentIndex;
            } else {
                if (fragmentIndex != pList->getF()-1){
                    pNode = pList->fragmentPointers[fragmentIndex+1];
                    index = this->pList->fragmentMaxSize*(fragmentIndex+1);
                } else {
                    pNode = nullptr;
                    index = pList->size();
                }
            }
        }

        Iterator &operator=(const Iterator &iterator){
            this->index=iterator.index;
            this->pList=iterator.pList;
            this->pNode=iterator.pNode;
            return *this;
        }

        T &operator*()
        {
            if (this->pNode == nullptr) throw std::out_of_range("Segmentation fault!");
            return this->pNode->data;
        }

        bool operator!=(const Iterator &iterator)
        {
            if (this->index != iterator.index || this->pNode != iterator.pNode) return 1;
            return 0;
        }

        void remove()
        {
            this->pNode= this->pNode->prev;
            this->pList->removeAt(this->index);
            this->index--;
        }

        void set(const T& element)
        {
            this->pNode->data = element;
        }

        Iterator &operator++()
        {
            this->index++;
            this->pNode = this->pNode->next;
            return *this;
        }
        Iterator operator++(int i)
        {
            Iterator a = *this;
            this->index ++;
            this->pNode= this->pNode->next;
            return a;
        }

    };
};

template <class T>
void FragmentLinkedList<T>::displayfList()
{
    for (int i=0;i < this->numfrag; i++)
        if (this->fragmentPointers[i] == nullptr) cout <<"empty\t";
        else cout << "fragment["<<i<<"]: "<<this->fragmentPointers[i]->data<<"\t";

}

template <class T>
string FragmentLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node *ptr = this->fragmentPointers[0];
    if (this->count == 0)
        ss << "]";
    else {
        ss << ptr->data;
        ptr=ptr->next;

        while (ptr != nullptr){
            ss <<", "<< ptr->data;
            ptr = ptr->next;
        }
        ss <<"]";
    }
    return ss.str();
}

template <class T>
void FragmentLinkedList<T>::add(const T& element)
{
    if (fragmentPointers[0] == nullptr){
        fragmentPointers[0] = new Node();
        fragmentPointers[0]->data = element;
        this->count ++;
        fragmentPointers[1] = fragmentPointers[0];
    } else {
        Node *tmp = fragmentPointers[0];
        while (tmp->next != nullptr) tmp = tmp->next;
        tmp->next = new Node();
        tmp->next->data = element;
        tmp->next->prev = tmp;
        tmp->next->next = nullptr;
        this->count ++;
        if (this->count	% this->fragmentMaxSize != 1 || this->count < this->fragmentMaxSize	){
            fragmentPointers[this->numfrag-1] = tmp->next;
        } else {
            this->numfrag ++;
            setFragment();
        }
    }

}

template<class T>
void FragmentLinkedList<T>::add(int index, const T& element)
{
	if (index < 0 || index > this->count) throw std::out_of_range("The index is out of range!");
	else {
		Node *tmp;
		if (index == 0){
			tmp = new Node();
			tmp->data = element;
			if (this->count) {
                tmp->next = fragmentPointers[0];
                fragmentPointers[0]->prev = tmp;
                fragmentPointers[0] = tmp;
			} else fragmentPointers[0] = tmp;
		} else if (index < count){
			tmp = fragmentPointers[0];
			while (index && tmp->next != nullptr){
				tmp = tmp->next;
				index--;
			}
			Node *p = new Node();
			p->data = element;
			p->next = tmp;
			p->prev= tmp->prev;
			tmp->prev->next = p;
			tmp->prev = p;

		} else {
			tmp = fragmentPointers[0];
        	while (tmp->next != nullptr) tmp = tmp->next;
	        tmp->next = new Node();
	        tmp->next->data = element;
    	    tmp->next->prev = tmp;
        	tmp->next->next = nullptr;
		}
		this->count++;
		if (this->count	%this->fragmentMaxSize == 1 && this->count > this->fragmentMaxSize) this->numfrag ++;
		setFragment();
	}
}

template<class T>
T FragmentLinkedList<T>::removeAt(int index)
{
	T removeE;
	if (index < 0 || index > this->count - 1){
		throw std::out_of_range("The index is out of range!");
	} else if (this->count == 1){
		removeE = this->fragmentPointers[0]->data;
		delete [] this->fragmentPointers[0];
		delete [] this->fragmentPointers[1];
		this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
        this->count--;
	} else {
		Node *tmp = this->fragmentPointers[0];
		while(index){
			index--;
			tmp=tmp->next;
		}
		if(tmp->prev == nullptr) {
			this->fragmentPointers[0] = tmp->next;
			tmp->next->prev = nullptr;
		} else if(tmp->next	== nullptr){
			tmp->prev->next = nullptr;
		}else {
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
		}
		removeE = tmp->data;
		delete [] tmp;
		tmp = nullptr;
		this->count --;
	    if (!(this->count%this->fragmentMaxSize)){
	        this->numfrag --;
	    }
        setFragment();
	}
	return removeE;
}

template<class T>
bool FragmentLinkedList<T>::removeItem(const T& item)
{
    Node *tmp = this->fragmentPointers[0];

    while (tmp != nullptr){

        if (tmp->data == item){
            if (this->count == 1){
                delete [] this->fragmentPointers[0];
                delete [] this->fragmentPointers[1];
                this->fragmentPointers[0] = NULL;
                this->fragmentPointers[1] = NULL;
                this->count--;
            } else {
                if(tmp->prev == nullptr) {
                    this->fragmentPointers[0] = tmp->next;
                    tmp->next->prev = nullptr;
                } else if(tmp->next	== nullptr){
                    tmp->prev->next = nullptr;
                }else {
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                }
                delete [] tmp;
                tmp = nullptr;
                this->count --;
                if (!(this->count%this->fragmentMaxSize)){
                    this->numfrag --;
                }
                setFragment();
            }
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

template <class T>
void FragmentLinkedList<T>::clear()
{
    this->fragmentPointers[0]=this->fragmentPointers[0]->next;
    while(this->fragmentPointers[0]->next == nullptr){
        delete [] this->fragmentPointers[0]->prev;
        this->fragmentPointers[0]=this->fragmentPointers[0]->next;
    }
    delete [] this->fragmentPointers[0];
    this->fragmentPointers = new Node* [2];
    this->fragmentPointers[0] = nullptr;
    this->fragmentPointers[1] = nullptr;
    this->numfrag = 2;
    this->count = 0;
}

template <class T>
T FragmentLinkedList<T>::get(int index)
{
    if (index > this->count - 1 || index < 0)
    throw std::out_of_range("The index is out of range!");
    else {
        Node *tmp = this->fragmentPointers[0];
		while(index){
			index--;
			tmp=tmp->next;
		}
        return tmp->data;
    }
}

template <class T>
void FragmentLinkedList<T>::set(int index, const T& element)
{
    if (index < 0 || index > this->count - 1)
		throw std::out_of_range("The index is out of range!");
    else {
        Node *tmp = this->fragmentPointers[0];
		while(index){
			index--;
			tmp=tmp->next;
		}
		tmp->data = element;
    }
}

template <class T>
int FragmentLinkedList<T>::indexOf(const T& item)
{
    int index=0;
    Node *tmp = fragmentPointers[0];
    while (tmp->data != item && tmp->next != nullptr){
        index ++;
        tmp = tmp->next;
    }
    if (tmp->data == item) return index;
    else return -1;
}

template <class T>
bool FragmentLinkedList<T>::contains(const T& item)
{
    Node *tmp = fragmentPointers[0];
    while (tmp->data != item && tmp->next != nullptr){
        tmp = tmp->next;
    }
    return tmp->data == item? 1:0;
}

#endif
// END: STUDENT ANSWER

