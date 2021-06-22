#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#ifndef _SPLAY_
#define _SPLAY_

template <class K, class V>
class SplayTree {
public:
    class Entry {
    public:
        K key;
        V value;

        Entry(K key, V value) : key(key), value(value) {};
        ~Entry() {};
    };

    class Node {
        Entry* entry;
        Node* left;
        Node* right;
        Node* parent;
        friend class SplayTree;

        Node(Entry* entry = NULL, Node* parent = NULL, Node* left = NULL, Node* right = NULL) {
            this->entry = entry;
            this->parent = parent;
            this->left = left;
            this->right = right;
        }
        ~Node() {
            if (entry != nullptr) delete entry;
            parent = nullptr;
            entry = nullptr;
            left = nullptr;
            right = nullptr;
        }
    };
private:

    
    void add(Entry* entry, Node*& root) {
        if (root == nullptr) {
            root = new Node(entry);
            return;
        }
        if (entry->key < root->entry->key) {
            add(entry, root->left);
        }
        else if (entry->key > root->entry->key) {
            add(entry, root->right);
        }
        else {
            throw "Duplicate key";
        }
    }
    
    bool Splay(Node*& root, K key) {
        if (key < root->entry->key) {
            if (key < root->left->entry->key) {
                if (Splay(root->left->left, key)) {
                    rotR(root);
                    rotR(root);
                }
                else {
                    if (key < root->left->left->entry->key) {
                        rotR(root->left);
                        rotR(root->left);
                    }
                    else {
                        rotL(root->left->left);
                        rotR(root->left);
                    }
                    if (this->root == root) rotR(root);
                    return 0;
                }
            }
            else if (key > root->left->entry->key) {
                if (Splay(root->left->right, key)) {
                    rotL(root->left);
                    rotR(root);
                }
                else {
                    if (key > root->left->right->entry->key) {
                        rotL(root->left);
                        rotL(root->left);
                    }
                    else {
                        rotR(root->left->right);
                        rotL(root->left);
                    }
                    if (this->root == root) rotR(root);
                    return 0;
                }
            }
            else {
                if (this->root == root) rotR(root);
                return 0;
            }
        }
        else if (key > root->entry->key) {
            if (key > root->right->entry->key) {
                if (Splay(root->right->right, key)) {
                    rotL(root);
                    rotL(root);
                }
                else {
                    if (key > root->right->right->entry->key) {
                        rotL(root->right);
                        rotL(root->right);
                    }
                    else {
                        rotR(root->right->right);
                        rotL(root->right);
                    }
                    if (this->root == root) rotL(root);
                    return 0;
                }
            }
            else if (key < root->right->entry->key) {
                if (Splay(root->right->left, key)) {
                    rotR(root->right);
                    rotL(root);
                }
                else {
                    if (key < root->right->left->entry->key) {
                        rotR(root->right);
                        rotR(root->right);
                    }
                    else {
                        rotL(root->right->left);
                        rotR(root->right);
                    }
                    if (this->root == root) rotL(root);
                    return 0;
                }
            }
            else {
                if (this->root == root) rotL(root);
                return 0;
            }
        }
        return 1;

        /*
        if (key < root->entry->key) {
            if (key < root->left->entry->key) {
                int tmp = Splay(root->left->left, key);
                if (tmp == 1) {
                    rotR(root);
                    rotR(root);
                }
                else {
                    if (key < root->left->left->entry->key) {
                        rotR(root->left);
                        rotR(root->left);
                    }
                    else {
                        rotR(root->left->left);
                        rotL(root->left);
                    }
                    if (this->root == root) rotR(root);
                    return 0;
                }
            }
            else if (key > root->left->entry->key) {
                int tmp = Splay(root->left->right, key);
                if (tmp == 1) {
                    rotL(root->left);
                    rotR(root);
                }
                else {
                    if (key > root->left->right->entry->key) {
                        rotL(root->left);
                        rotL(root->left);
                    }
                    else {
                        rotR(root->left->right);
                        rotL(root->left);
                    }
                    if (this->root == root) rotR(root);
                    return 0;
                }
            }
            else {
                return 0;
            }
        }
        else if (key > root->entry->key) {
            if (key > root->right->entry->key) {
                if (Splay(root->right->right, key)) {
                    rotL(root);
                    rotL(root);
                }
                else {
                    if (key > root->right->right->entry->key) {
                        rotL(root->right);
                        rotL(root->right);
                    }
                    else {
                        rotR(root->right->right);
                        rotL(root->right);
                    }
                    if (this->root == root) rotL(root);
                    return 0;
                }
            }
            else if (key < root->right->entry->key) {
                if (Splay(root->right->left, key)) {
                    rotR(root->right);
                    rotL(root);
                }
                else {
                    if (key < root->right->left->entry->key) {
                        rotR(root->right);
                        rotR(root->right);
                    }
                    else {
                        rotL(root->right->left);
                        rotR(root->right);
                    }
                    if (this->root == root) rotR(root);
                    return 0;
                }
            }
            else {
                return 0;
            }
        }
        return 1;
        
        /*
        if (root == nullptr) return;
        if (key < root->entry->key) {
            if (root->left == nullptr) return ;
            if (key < root->left->entry->key) {
                Splay(root->left->left, key);
                rotR(root);
            }
            else if (key > root->left->entry->key) {
                Splay(root->left->right, key);
                if (root->left->right != nullptr) 
                    rotL(root->left);
            }

            if (root->left == nullptr) return;
            else rotR(root);
        }
        else if (key > root->entry->key) {
            if (root->right == nullptr) return;
            if (key < root->right->entry->key) {
                Splay(root->right->left, key);
                if (root->right->left != nullptr)
                    rotR(root->right);
            }
            else if (key > root->right->entry->key) {
                Splay(root->right->right, key);
                rotL(root);
            }

            if (root->right == nullptr) return;
            else rotL(root);
        }*/
    }
    
public:
    Node* root;
    Node* addedNode;

    SplayTree() : root(NULL) {};
    ~SplayTree() { this->clear(); };
    void rotL(Node*& root) {
        Node* tmp = root->right;
        root->right = tmp->left;
        tmp->left = root;
        root = tmp;
        /*if (root->left->right != nullptr) {
            root->left->right->parent = root->left;
        }*/
    }
    void rotR(Node*& root) {
        Node* tmp = root->left;
        root->left = tmp->right;
        tmp->right = root;
        root = tmp;
        /*if (root->right->left != nullptr) {
            root->right->left->parent = root->right;
        }*/
    }
    void add(K key, V value) {
        Entry* tmp = new Entry(key, value);
        add(tmp, this->root);
        Splay(this->root, key);
    }
    void add(Entry* entry) {
        add(entry, this->root);
        Splay(this->root, entry->key);
    }

    void remove(K key) {
        Node* tmp = this->root;
        while (tmp != nullptr && tmp->entry->key != key) {
            if (key < tmp->entry->key) tmp = tmp->left;
            else if (key > tmp->entry->key) tmp = tmp->right;
        }
        if (tmp == nullptr) throw "Not found";
        Splay(this->root, key);
        if (this->root->left == nullptr) {
            this->root = this->root->right;
            delete tmp;
            tmp = nullptr;
        }
        else if (this->root->right == nullptr) {
            this->root = this->root->left;
            delete tmp;
            tmp = nullptr;
        }
        else {
            Node* tmp2 = this->root->left;
            while (tmp2->right != nullptr) {
                tmp2 = tmp2->right;
            }
            this->root = this->root->left;
            Splay(this->root, tmp2->entry->key);
            this->root->right = tmp->right;
            tmp2 = nullptr;
            delete tmp;
            tmp = nullptr;
        }
    }

    /*
    V search(K key) {

    }*/
    void traverseNLR(void (*func)(K key, V value), Node* pR) {
        if (pR) {
            func(pR->entry->key, pR->entry->value);
            traverseNLR(func, pR->left);
            traverseNLR(func, pR->right);
        }
    }
    void traverseNLR(void (*func)(K key, V value)) {
        traverseNLR(func, this->root);
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

#endif
