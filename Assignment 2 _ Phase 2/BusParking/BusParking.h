#include <iostream>
#include <string.h>

#ifndef _BUSPARKING_
#define _BUSPARKING_

class BusParking
{
public:
    class Entry {
    public:
        int start;
        int end;
        int val;
        friend class BusParking;

        Entry(int start, int end) {
            this->start = start;
            this->end = end;
            this->val = 0;
        }
        ~Entry() {};
    };
    enum BalanceValue
    {
        LH = -1,
        EH = 0,
        RH = 1
    };
    class Node {
        Entry* entry;
        Node* left;
        Node* right;
        BalanceValue balance;
        friend class AVLTree;
        friend class BusParking;

        Node(Entry* entry = NULL, Node* left = NULL, Node* right = NULL) {
            this->entry = entry;
            this->left = left;
            this->right = right;
            this->balance = EH;
        }
        ~Node() {
            if (entry != nullptr) delete entry;
            entry = nullptr;
            left = right = nullptr;
        }
    };
    class AVLTree {
        friend class BusParking;

    public:
        Node* root;
        int size;

        AVLTree() { this->root = nullptr; size = 0; }
        ~AVLTree() { this->clear(); }

        int getHeightRec(Node* node)
        {
            if (node == NULL)
                return 0;
            int lh = this->getHeightRec(node->left);
            int rh = this->getHeightRec(node->right);
            return (lh > rh ? lh : rh) + 1;
        }
        void add(Node*& root, Entry*& entry) {
            if (root == nullptr) {
                root = new Node(entry);
                size++;
            }
            else {

                if (entry->end < root->entry->end ||
                    (entry->end == root->entry->end && entry->start < root->entry->start)) {
                    int oldH = getHeightRec(root->left);
                    this->add(root->left, entry);
                    if (oldH < getHeightRec(root->left)) {
                        if (root->balance == LH)
                            balanceLeft(root);
                        else if (root->balance == EH)
                            root->balance = LH;
                        else root->balance = EH;
                    }
                }
                else {
                    int oldH = getHeightRec(root->right);
                    this->add(root->right, entry);
                    if (oldH < getHeightRec(root->right)) {
                        if (root->balance == RH)
                            balanceRight(root);
                        else if (root->balance == EH)
                            root->balance = RH;
                        else root->balance = EH;
                    }
                }
            }

        }
        /*
        void remove(Node*& root, const K& key) {
            if (root == nullptr) throw "Not found";
            if (key < root->entry->key) {
                int oldH = getHeightRec(root->left);
                remove(root->left, key);
                if (oldH > getHeightRec(root->left)) {
                    balanceRight_Del(root);
                }
            }
            else if (key > root->entry->key) {
                int oldH = getHeightRec(root->right);
                remove(root->right, key);
                if (oldH > getHeightRec(root->right)) {
                    balanceLeft_Del(root);
                }
            }
            else {
                if (root->left == nullptr) {
                    Node* tmp = root;
                    root = root->right;
                    delete tmp;
                    tmp = nullptr;
                }
                else if (root->right == nullptr) {
                    Node* tmp = root;
                    root = root->left;
                    delete tmp;
                    tmp = nullptr;
                }
                else {
                    Node* tmp = root->left;
                    while (tmp->right != nullptr) {
                        tmp = tmp->right;
                    }
                    root->entry->key = tmp->entry->key;
                    root->entry->value = tmp->entry->value;
                    int oldH = getHeightRec(root->left);
                    remove(root->left, tmp->entry->key);
                    if (oldH > getHeightRec(root->left)) {
                        balanceRight_Del(root);
                    }
                }
            }
        }
        */
        void rotL(Node*& root) {
            Node* tmp = root->right;
            root->right = tmp->left;
            tmp->left = root;
            root = tmp;
        }
        void rotR(Node*& root) {
            Node* tmp = root->left;
            root->left = tmp->right;
            tmp->right = root;
            root = tmp;
        }
        bool balanceLeft(Node*& root) {
            if (root->left->balance == LH) {
                root->balance = EH;
                rotR(root);
                root->balance = EH;
                return 0;
            }
            else {
                if (root->left->right->balance == LH) {
                    root->balance = RH;
                    root->left->balance = EH;
                }
                else if (root->left->right->balance == EH) {
                    root->balance = EH;
                    root->left->balance = EH;
                }
                else {
                    root->balance = EH;
                    root->left->balance = LH;
                }
                root->left->right->balance = EH;
                rotL(root->left);
                rotR(root);
                return 1;
            }
        }
        bool balanceRight(Node*& root) {
            if (root->right->balance == RH) {
                root->balance = EH;
                rotL(root);
                root->balance = EH;
                return 0;
            }
            else {
                if (root->right->left->balance == RH) {
                    root->right->balance = EH;
                    root->balance = LH;
                }
                else if (root->right->left->balance == EH) {
                    root->balance = EH;
                    root->right->balance = EH;
                }
                else {
                    root->balance = EH;
                    root->right->balance = RH;
                }
                root->right->left->balance = EH;
                rotR(root->right);
                rotL(root);
                return 1;
            }
        }
        void add(Entry* entry) {
            add(this->root, entry);
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
                if (root->left->balance == RH) {
                    if (root->left->right->balance == LH) {
                        root->balance = RH;
                        root->left->balance = EH;

                    }
                    else if (root->left->right->balance == EH) {
                        root->balance = EH;
                        root->left->balance = EH;
                    }
                    else {
                        root->balance = EH;
                        root->left->balance = LH;
                    }
                    root->left->right->balance = EH;
                    rotL(root->left);
                    rotR(root);
                }
                else {
                    if (root->left->balance == EH) {
                        root->left->balance = RH;
                    }
                    else { // LH
                        root->balance = EH;
                        root->left->balance = EH;
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
                if (root->right->balance == LH) {
                    if (root->right->left->balance == RH) {
                        root->balance = LH;
                        root->right->balance = EH;
                    }
                    else if (root->right->left->balance == EH) {
                        root->balance = EH;
                        root->right->balance = EH;
                    }
                    else {
                        root->balance = EH;
                        root->right->balance = RH;
                    }
                    root->right->left->balance = EH;
                    rotR(root->right);
                    rotL(root);
                }
                else {
                    if (root->right->balance == EH) {
                        root->right->balance = LH;
                    }
                    else { // RH
                        root->balance = EH;
                        root->right->balance = EH;
                    }
                    rotL(root);
                }
                return 1;
            }
        }
        

        void clear(Node* root) {
            if (root != nullptr) {
                clear(root->left);
                clear(root->right);
                delete root;
                root = nullptr;
            }
        }
        void clear() {
            clear(this->root);
        }
    };
public:
    AVLTree *BusTree;
    int min = 0;
    BusParking() {
        BusTree = new AVLTree();
    }
    void add(int s, int t) {
        Entry* tmp = new Entry(s, t);
        BusTree->add(tmp);
        Node* tmpN = BusTree->root;
        int less = 0;
        while (tmpN != nullptr ) {
            if (tmpN->entry->end <= s) {
                less++;
                tmpN = tmpN->left;
            }
            else {
                tmpN = tmpN->right;
            }
        }
        if (BusTree->size - less > min) min = BusTree->size - less;
    }
    int minPark() {
        return min;
    }

};

#endif