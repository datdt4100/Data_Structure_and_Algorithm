#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

#ifndef _AVL_TREE_
#define _AVL_TREE_

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int& n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node* root;
protected:
    int getHeightRec(Node* node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
    
    void insert(Node* &root, const T& value) {
        if (root == nullptr) {
            root = new Node(value);
            
        }
        else {
            if (value < root->data) {
                int oldH = getHeightRec(root->pLeft);
                this->insert(root->pLeft, value);
                if (oldH < getHeightRec(root->pLeft)) {
                    if (root->balance == LH)
                        balanceLeft(root);
                    else if (root->balance == EH)
                        root->balance = LH;
                    else root->balance = EH;
                }

            }
            else {
                int oldH = getHeightRec(root->pRight);
                this->insert(root->pRight, value);
                if (oldH < getHeightRec(root->pRight)) {
                    if (root->balance == RH)
                        balanceRight(root);
                    else if (root->balance == EH)
                        root->balance = RH;
                    else root->balance = EH;
                }
            }
        }
    }
    
    void remove(Node*& root, const T& value) {
        if (root == nullptr) return;
        if (value < root->data) {
            int oldH = getHeightRec(root->pLeft);
            remove(root->pLeft, value);
            if (oldH > getHeightRec(root->pLeft)) {
                balanceRight_Del(root);
            }
        }
        else if (value > root->data) {
            int oldH = getHeightRec(root->pRight);
            remove(root->pRight, value);
            if (oldH > getHeightRec(root->pRight)) {
                balanceLeft_Del(root);
            }
        }
        else {
            if (root->pLeft == nullptr) {
                Node* tmp = root;
                root = root->pRight;
                delete tmp;
                tmp = nullptr;
            }
            else if (root->pRight == nullptr) {
                Node* tmp = root;
                root = root->pLeft;
                delete tmp;
                tmp = nullptr;
            }
            else {
                Node* tmp = root->pRight;
                while (tmp->pLeft != nullptr) {
                    tmp = tmp->pLeft;
                }
                root->data = tmp->data;
                int oldH = getHeightRec(root->pLeft);
                remove(root->pRight, tmp->data);
                if (oldH > getHeightRec(root->pRight)) {
                    balanceLeft_Del(root);
                }
            }
        }
    }
    
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node*> q;
        q.push(root);
        Node* temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }
    void rotL(Node*& root) {
        Node* tmp = root->pRight;
        root->pRight = tmp->pLeft;
        tmp->pLeft = root;
        root = tmp;
    }
    void rotR(Node*& root) {
        Node* tmp = root->pLeft;
        root->pLeft = tmp->pRight;
        tmp->pRight = root;
        root = tmp;
    }

    bool balanceLeft(Node*& root) {
        if (root->pLeft->balance == LH) {
            root->balance = EH;
            rotR(root);
            root->balance = EH;
            return 0;
        }
        else {
            if (root->pLeft->pRight->balance == LH) {
                root->balance = RH;
                root->pLeft->balance = EH;
            }
            else if (root->pLeft->pRight->balance == EH) {
                root->balance = EH;
                root->pLeft->balance = EH;
            }
            else {
                root->balance = EH;
                root->pLeft->balance = LH;
            }
            root->pLeft->pRight->balance = EH;
            rotL(root->pLeft);
            rotR(root);
            return 1;
        }
    }
    bool balanceRight(Node*& root) {
        if (root->pRight->balance == RH) {
            root->balance = EH;
            rotL(root);
            root->balance = EH;
            return 0;
        }
        else {
            if (root->pRight->pLeft->balance == RH) {
                root->pRight->balance = EH;
                root->balance = LH;
            }
            else if (root->pRight->pLeft->balance == EH) {
                root->balance = EH;
                root->pRight->balance = EH;
            }
            else {
                root->balance = EH;
                root->pRight->balance = RH;
            }
            root->pRight->pLeft->balance = EH;
            rotR(root->pRight);
            rotL(root);
            return 1;
        }
    }
    void insert(const T& value)
    {
        insert(this->root, value);
    }

    bool balanceLeft_Del(Node*& root) {
        if (root->balance == RH) {
            root->balance = EH;
            return 0;
        }
        else if (root->balance == EH) {
            root->balance = LH;
            return 0;
        }
        else {
            if (root->pLeft->balance == RH) {
                if (root->pLeft->pRight->balance == LH) {
                    root->balance = RH;
                    root->pLeft->balance = EH;

                }
                else if (root->pLeft->pRight->balance == EH) {
                    root->balance = EH;
                    root->pLeft->balance = EH;
                }
                else {
                    root->balance = EH;
                    root->pLeft->balance = LH;
                }
                root->pLeft->pRight->balance = EH;
                rotL(root->pLeft);
                rotR(root);
            }
            else {
                if (root->pLeft->balance == EH) {
                    root->pLeft->balance = RH;
                }
                else { // LH
                    root->balance = EH;
                    root->pLeft->balance = EH;
                }
                rotR(root);
            }
            return 1;
        }
    }
    bool balanceRight_Del(Node*& root) {
        if (root->balance == LH) {
            root->balance = EH;
            return 0;
        }
        else if (root->balance == EH) {
            root->balance = RH;
            return 0;
        }
        else {
            if (root->pRight->balance == LH) {
                if (root->pRight->pLeft->balance == RH) {
                    root->balance = LH;
                    root->pRight->balance = EH;

                }
                else if (root->pRight->pLeft->balance == EH) {
                    root->balance = EH;
                    root->pRight->balance = EH;
                }
                else {
                    root->balance = EH;
                    root->pRight->balance = RH;
                }
                root->pRight->pLeft->balance = EH;
                rotR(root->pRight);
                rotL(root);
            }
            else {
                if (root->pRight->balance == EH) {
                    root->pRight->balance = LH;
                }
                else { // RH
                    root->balance = EH;
                    root->pRight->balance = EH;
                }
                rotL(root);
            }
            return 1;
        }
    }
    void remove(const T& value)
    {
        //TODO
        remove(this->root, value);
    }

    BalanceValue getBV(Node* root, const T& value) {
        if (root != nullptr) {
            if (value < root->data) {
                return getBV(root->pLeft, value);
            }
            else if (value > root->data) {
                return getBV(root->pRight, value);
            }
            else {
                return root->balance;
            }
        }
    }
    BalanceValue getBV(const T& value) {
        return getBV(this->root, value);
    }

    class Node
    {
    private:
        T data;
        Node* pLeft, * pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

#endif
