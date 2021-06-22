#include <iostream>
#include <string.h>
using namespace std;

#ifndef _DOUBLE_LL_
#define _DOUBLE_LL_
template <class T>
class DoubleLList {
public:
	class Node {
	private:
		T value;
		Node* prev;
		Node* next;
		friend class DoubleLList;
	public:
		Node() : value(0), prev(nullptr), next(nullptr) {};
		Node(T value, Node* prev = nullptr, Node* next = nullptr) {
			this->value = value;
			this->prev = prev;
			this->next = next;
		}
	};
protected:
	Node* DList;
	int size;
public:
	DoubleLList() : DList(nullptr), size(0) {};
	~DoubleLList() { clear(); }

	virtual void add(T value);
	virtual void addAt(T value, int idx);
	virtual void removeValue(T value);
	virtual void removeAt(int idx);
	virtual bool isEmpty() { return size; }
	virtual void show();
	virtual void clear();
};
template <class T>
void DoubleLList<T>::add(T value) {
	if (this->DList == nullptr) DList = new Node(value);
	else {
		Node* tmp = this->DList;
		while (tmp->next != nullptr) {
			tmp = tmp->next;
		}
		tmp->next = new Node(value);
		tmp->next->prev = tmp;
	}
	this->size++;
}

template <class T>
void DoubleLList<T>::addAt(T value, int idx) {
	Node* tmp = new Node(value);
	if (idx <= 0) {
		tmp->next = this->DList;
		this->DList->prev = tmp;
		this->DList = tmp;
	}
	else if (idx >= this->size) {
		Node* tmp1 = DList;
		while (tmp1->next != nullptr) {
			tmp1 = tmp1->next;
		}
		tmp1->next = tmp;
		tmp->prev = tmp1;
	}
	else {
		Node* tmp1 = this->DList;
		while (idx > 1) {
			tmp1 = tmp1->next;
			idx--;
		}
		tmp1->next->prev = tmp;
		tmp->next = tmp1->next;
		tmp1->next = tmp;
		tmp->prev = tmp1;
	}
	this->size++;
}

template <class T>
void DoubleLList<T>::removeValue(T value) {
	Node* p = this->DList;
	bool check = 0;
	while (p != nullptr) {
		if (p->value == value) {
			check = 1;
			if (p->prev == nullptr) {
				this->DList = p->next;
				p = p->next;
				delete p->prev;
				p->prev = nullptr;
			}
			else if (p->next == nullptr) {
				p = p->prev;
				delete p->next;
				p->next = nullptr;
				p = p->next;
			}
			else {
				Node* tmp = p;
				p->prev->next = p->next;
				p->next->prev = p->prev;
				p = p->next;
				delete tmp;
				tmp = nullptr;
			}
			this->size--;
		}
		else p = p->next;
	}
	if (!check) cout << "No such value!\n";
}

template <class T>
void DoubleLList<T>::removeAt(int idx) {
	if (this->size == 0) {
		cout << "No element\n";
		return;
	}
	if (this->size == 1) {
		delete this->DList;
		this->DList = nullptr;
		this->size--;
		return;
	}
	if (idx < 1) {
		this->DList = this->DList->next;
		delete this->DList->prev;
		this->DList->prev = nullptr;
		this->size--;
		return;
	}
	if (idx >= this->size - 1) {
		Node* tmp = this->DList;
		while (tmp->next != nullptr) {
			tmp = tmp->prev;
			delete tmp->next;
			tmp->next = nullptr;
		}
		this->size--;
		return;
	}

	Node* tmp = this->DList;
	while (idx > 1) {
		tmp = tmp->next;
		idx--;
	}
	Node* p = tmp->next;
	tmp->next = p->next;
	p->next->prev = tmp;
	delete p;
	p = nullptr;
	this->size--;
}

template <class T>
void DoubleLList<T>::show() {
	if (this->size == 0) {
		cout << "Empty list!\n";
		return;
	}
	Node* p = this->DList;
	while (p != nullptr) {
		cout << p->value << " ";
		p = p->next;
	}
	cout << endl;
}

template <class T>
void DoubleLList<T>::clear() {
	if (this->size == 0) return;
	while (this->DList != nullptr) {
		Node* tmp = this->DList;
		this->DList = this->DList->next;
		delete tmp;
		tmp = nullptr;
	}
	this->size = 0;
}
#endif
