
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"


#ifndef _STACK_QUEUE_
#include "Stack_Queue.h"
#define _STACK_QUEUE_
#endif

#ifndef _BST_
#define _BST_

template<class T>
class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    //Helping function
    Node* add(Node* root, T value)
    {
        if (root == nullptr) {
            root = new Node(value);
        }
        else {
            if (value <= root->value)
                root->pLeft = add(root->pLeft, value);
            else root->pRight = add(root->pRight, value);
        }
        return root;
    }

    void SwapValue(Node* tmp1, Node* tmp2) {
        tmp1->value = tmp1->value + tmp2->value;
        tmp2->value = tmp1->value - tmp2->value;
        tmp1->value = tmp1->value - tmp2->value;
    }

    T FindMinValue(Node* tmp)
    {
        if (tmp->pLeft == nullptr) return tmp->value;
        else return FindMinValue(tmp->pLeft);
    }

    Node* deleteNode(Node* root, T value)
    {
        if (root != nullptr) {
            if (value < root->value)
                root->pLeft = deleteNode(root->pLeft, value);
            else if (value > root->value)
                root->pRight = deleteNode(root->pRight, value);
            else
            {
                // root->data == value, delete this node
                if (root->pLeft == nullptr && root->pRight == nullptr) {
                    delete root;
                    root = nullptr;
                }
                else if (root->pLeft == nullptr)
                {
                    Node* newRoot = root->pRight;
                    delete root;
                    return newRoot;
                }
                else if (root->pRight == nullptr)
                {
                    Node* newRoot = root->pLeft;
                    delete root;
                    return newRoot;
                }
                else {
                    root->value = std::move(this->FindMinValue(root->pRight));
                    root->pRight = deleteNode(root->pRight, root->value);
                }
            }
        }
        return root;
    }

    void add(T value) {
        //TODO
        this->root = add(this->root, value);
    }

    void deleteNode(T value) {
        //TODO
        this->root = this->deleteNode(this->root, value);
    }

    bool find(Node* root, T i) {
        if (root == nullptr) return 0;
        if (i < root->value) return find(root->pLeft, i);
        else if (i > root->value) return find(root->pRight, i);
        else return 1;
    }

    bool find(T i) {
        // TODO: return true if value i is in the tree; otherwise, return false.
        return find(this->root, std::move(i));
    }

    T sum(Node* root, T l, T r) {
        if (root == nullptr) return 0;
        if (root->value <= r && root->value >= l)
            return root->value + sum(root->pRight, l, r) + sum(root->pLeft, l, r);
        else return sum(root->pRight, l, r) + sum(root->pLeft, l, r);
        // TODO: return the sum of all element in the tree has value in range [l,r].

    }

    T sum(T l, T r) {
        // TODO: return the sum of all element in the tree has value in range [l,r].
        return sum(this->root, l, r);
    }

    T getMin(Node* root) {
        if (root == nullptr) return -1;
        if (root->pLeft == nullptr) return root->value;
        else {
            return getMin(root->pLeft);
        }
    }

    T getMin() {
        //TODO: return the minimum values of nodes in the tree.
        return getMin(this->root);
    }

    T getMax(Node* root) {
        if (root == nullptr) return -1;
        if (root->pRight == nullptr) return root->value;
        else {
            return getMax(root->pRight);
        }
    }

    T getMax() {
        return getMax(this->root);
        //TODO: return the maximum values of nodes in the tree.

    }



    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }

    string inOrder() {
        return inOrderRec(this->root);
    }

    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};

template<class K, class V>
class BinaryTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;
    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node* walker = this->root;
        int l = (int)posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }

    //Helping functions

    /* Function to find height of a tree */
    int height(Node* root, int& ans)
    {
        if (root == nullptr)
            return 0;

        int left_height = height(root->pLeft, ans);

        int right_height = height(root->pRight, ans);

        // update the answer, because diameter of a 
        // tree is nothing but maximum value of 
        // (left_height + right_height + 1) for each node 
        ans = max(ans, 1 + left_height + right_height);

        return 1 + max(left_height, right_height);
    }

    /* Computes the diameter of binary tree with given root. */
    int getDiameter()
    {
        if (this->root == nullptr)
            return 0;
        int ans = -1; // This will store the final answer 
        height(this->root, ans);
        return ans;
    }

    void BFS()
    {
        stringstream result;
        if (this->root == nullptr) return;
        Queue<Node*> _BFS;
        _BFS.enqueue(this->root);
        while (!_BFS.isEmpty()) {
            Node* tmp = _BFS.Front();
            _BFS.dequeue();
            result << tmp->value;
            if (tmp->pLeft != nullptr) _BFS.enqueue(tmp->pLeft);
            if (tmp->pRight != nullptr) _BFS.enqueue(tmp->pRight);
            if (!_BFS.isEmpty()) result << " ";
        }
        /*
        queue<Node*> BreathFirstSearch;
        BreathFirstSearch.push(this->root);
        while (!BreathFirstSearch.empty()) {
            Node* tmp = BreathFirstSearch.front();
            BreathFirstSearch.pop();
            result << tmp->value;
            if (tmp->pLeft != nullptr) BreathFirstSearch.push(tmp->pLeft);
            if (tmp->pRight != nullptr) BreathFirstSearch.push(tmp->pRight);
            if (!BreathFirstSearch.empty()) result << " ";
        }*/
        cout << result.str();
    }

    int countTwoChildrenNode(Node* root) {
        if (root->pLeft == nullptr && root->pRight == nullptr) {
            return 0;
        }
        else if (root->pLeft == nullptr) {
            return countTwoChildrenNode(root->pRight);
        }
        else if (root->pRight == nullptr) {
            return countTwoChildrenNode(root->pLeft);
        }
        else return 1 + countTwoChildrenNode(root->pLeft) + countTwoChildrenNode(root->pRight);
    }

    int countTwoChildrenNode()
    {
        return countTwoChildrenNode(this->root);
    }

    bool isBST(Node* root) {
        if (root == nullptr) return 1;
        if (root->pLeft != nullptr && root->pRight != nullptr){
            if (root->pLeft->value > root->value || root->pRight->value <= root->value)
                return 0;
        }
        else if (root->pLeft != nullptr) {
            if (root->pLeft->value > root->value)
                return 0;
        }
        else if (root->pRight != nullptr) {
            if (root->pRight->value <= root->value)
                return 0;
        }
        return isBST(root->pLeft) && isBST(root->pRight);
    }
    bool isBST() {
        return isBST(this->root);
        // TODO: return true if a tree is a BST; otherwise, return false.  
    }

    int getHeight(Node* root) {
        if (root == nullptr) return 0;
        return 1 + max(getHeight(root->pLeft), getHeight(root->pRight));
    }

    int getHeight() {
        return getHeight(this->root);
        // TODO: return height of the binary tree.

    }

    string preOrder(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << root->value <<" ";
            ss << preOrder(root->pLeft);
            ss << preOrder(root->pRight);
        }
        return ss.str();
    }

    string preOrder() {
        return preOrder(this->root);
        // TODO: return the sequence of values of nodes in pre-order.

    }

    string inOrder(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrder(root->pLeft);
            ss << root->value << " ";
            ss << inOrder(root->pRight);
        }
        return ss.str();
    }

    string inOrder() {
        return inOrder(this->root);
        // TODO: return the sequence of values of nodes in in-order.
    }

    string postOrder(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << postOrder(root->pLeft);
            ss << postOrder(root->pRight);
            ss << root->value << " ";
        }
        return ss.str();
    }

    string postOrder() {
        return postOrder(this->root);
        // TODO: return the sequence of values of nodes in post-order.

    }

    int sumOfLeafs(Node* root) {
        if (root == nullptr) return 0;
        if (root->pLeft == nullptr && root->pRight == nullptr)
            return root->value;
        else if (root->pLeft == nullptr)
            return sumOfLeafs(root->pRight);
        else if (root->pRight == nullptr)
            return sumOfLeafs(root->pLeft);
        else return sumOfLeafs(root->pLeft) + sumOfLeafs(root->pRight);
    }

    int sumOfLeafs() {
        //TODO
        return sumOfLeafs(this->root);
    }

};

#endif
