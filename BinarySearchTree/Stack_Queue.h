#ifndef _STACK_QUEUE_
#define _STACK_QUEUE_

template<class T>
class Stack{
public:
	class Node;
private:
	int cap, count;
	Node* head;
public:
	Stack(int cap = 100) {
		this->cap = cap;
		head = nullptr;
		count = 0;
	}
	~Stack() {
		clear();
	}

	bool isFull() {
		if (count < cap) return 0;
		return 1;
	}

	bool isEmpty() {
		return count ? 0 : 1;
	}

	int size() {
		return this->count;
	}

	void push(T data) {
		if (isFull()) {
			cout << "Stack is Full" << endl;
			return;
		}
		if (head == nullptr) {
			head = new Node(data);
		}
		else {
			Node* tmp = new Node(data, this->head);
			head = tmp;
		}
		count++;
	}

	void pop() {
		if (head == nullptr) {
			cout << "Stack is empty" << endl;
			return;
		}
		if (this->count == 1) {
			delete head;
			head = nullptr;
		}
		else {
			Node* tmp = this->head;
			this->head = this->head->next;
			delete tmp;
			tmp = nullptr;
		}
		count--;
	}

	T &top() {
		if (head != nullptr) return head->data;
	}

	void show() {
		if (this->head == nullptr) {
			cout << "Stack is empty";
			return;
		}
		Node* tmp = head;
		while (tmp != nullptr) {
			cout << tmp->data<<"\t";
			tmp = tmp->next;
		}
		cout << endl;
	}

	void clear() {
		while (head != nullptr) {
			Node* tmp = head;
			head = head->next;
			delete tmp;
			tmp = nullptr;
		}
		count = 0;
	}

	bool find(T& data) {
		if (this->head != nullptr) {
			Node* tmp = head;
			while (tmp != nullptr) {
				if (data == tmp->data) return 1;
				tmp = tmp->next;
			}
		}
		return 0;
	}

	class Node {
	private:
		Node* next;
		T data;
		friend class Stack;
	public:
		Node() : next(nullptr), data(0) {};
		Node(T data, Node* next = nullptr) {
			this->data = data;
			this->next = next;
		}
		~Node() {};
	};
};

template <class T>
class Queue {
public:
	class Node;
private:
	Node* head, * tail;
	int cap, count;
public:
	Queue(int _cap = 100) : head(nullptr), tail(nullptr), cap(_cap), count(0) {};
	~Queue() { this->clear(); }
	bool isFull() {
		if (this->count < this->cap) return 0;
		return 1;
	}

	bool isEmpty() {
		if (this->count == 0) return 1;
		return 0;
	}

	void enqueue(T data) {
		if (this->isFull()) {
			cout << "Queue is Full\n";
			return;
		}
		if (this->head == nullptr) {
			this->head = new Node(data);
			this->tail = this->head;
		}
		else {
			this->tail->next = new Node(data);
			this->tail = this->tail->next;
		}
		count++;

	}

	void dequeue() {
		if (this->isEmpty()) {
			cout << "Queue is Empty\n";
			return;
		}
		if (this->count == 1) {
			delete this->head;
			this->head = nullptr;
			this->tail = nullptr;
		}
		else {
			Node* tmp = this->head;
			this->head = this->head->next;
			delete tmp;
			tmp = nullptr;
		}
		count--;
	}
	T& Front() {
		if (!this->isEmpty()) return this->head->data;
	}

	T& Rear() {
		if (!this->isEmpty()) return this->tail->data;
	}

	int size() {
		return this->count;
	}

	void clear() {
		
		while (this->head != nullptr) {
			Node* tmp = this->head;
			this->head = this->head->next;
			delete tmp;
			tmp = nullptr;
		}
		this->head = this->tail = nullptr;
		this->count = 0;
	}

	class Node {
	private:
		Node* next;
		T data;
		friend class Queue;
	public:
		Node() : next(nullptr), data(0) {};
		Node(T data, Node* next = nullptr) {
			this->data = data;
			this->next = next;
		}
		~Node() {};
	};

};

#endif //

