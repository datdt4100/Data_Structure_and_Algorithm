#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#ifndef _BKUTree_
#define _BKUTree_
enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};
template <class K, class V>
class BKUTree {
public:
    class AVLTree;
    class SplayTree;

    class Entry {
    public:
        K key;
        V value;

        Entry(K key, V value) {
            this->key = key;
            this->value = value;
        }
        ~Entry() {};
    };

public:
    AVLTree* avl;
    SplayTree* splay;
    std::queue<K> keys;
    int maxNumOfKeys;

public:
    BKUTree(int maxNumOfKeys = 5) {
        this->maxNumOfKeys = maxNumOfKeys;
        avl = new AVLTree();
        splay = new SplayTree();
    }
    ~BKUTree() { this->clear(); }

    void add(K key, V value) {
        avl->add(key, value);
        splay->add(key, value);
        if ((int)keys.size() == maxNumOfKeys) {
            keys.pop();
        }
        keys.push(key);
        this->avl->addedNode->corr = this->splay->addedNode;
        this->splay->addedNode->corr = this->avl->addedNode;
    }
    void remove(K key) {
        avl->remove(key);
        splay->remove(key);
        int n = keys.size();
        for (int i = 0; i < n; i++) {
            K tmp = keys.front();
            keys.pop();
            if (tmp != key) keys.push(tmp);
        }
        if ((int)keys.size() == maxNumOfKeys) {
            keys.pop();
        }
        if (splay->root != nullptr) keys.push(splay->root->entry->key);
    }
    void showKeysList() {
        int n = keys.size();
        cout << "List Key" << endl;
        for (int i = 0; i < n; i++) {
            K tmp = keys.front();
            cout << tmp << "\t";
            keys.pop();
            keys.push(tmp);
        }
    }
    V search(K key, vector<K>& traversedList) {
        if (splay->root->entry->key == key) {
            traversedList.push_back(key);
            return splay->root->entry->value;
        }
        typename SplayTree::Node* tmp = nullptr;
        avl->search(key);
        bool check = 0;
        for (int i = 0; i < (int)keys.size(); i++) {
            K tmpkey = keys.front();
            keys.pop();
            if (tmpkey == key) check = 1;
            keys.push(tmpkey);
        }
        if (check == 1) {
            int count = 0;
            tmp = splay->root;
            while (tmp->entry->key != key) {
                traversedList.push_back(tmp->entry->key);
                if (key < tmp->entry->key) tmp = tmp->left;
                else if (key > tmp->entry->key) tmp = tmp->right;
                count++;
            }
            V tmpvalue = tmp->entry->value;

            if (count < 3) {
                splay->Splay(splay->root, key);
            }
            else if (key < tmp->entry->key) {
                tmp = tmp->parent->parent->parent;
                splay->Splay(tmp->left, key);
            }
            else if (key > tmp->entry->key) {
                tmp = tmp->parent->parent->parent;
                splay->Splay(tmp->right, key);
            }
            traversedList.push_back(key);
            if ((int)keys.size() == maxNumOfKeys) {
                keys.pop();
            }
            keys.push(key);
            return tmpvalue;
        }
        else {
            tmp = avl->search(splay->root->corr, key, traversedList);
            V tmpvalue = tmp->entry->value;
            if (tmp->parent->parent == nullptr || tmp->parent->parent->parent == nullptr) {
                splay->Splay(splay->root, key);
            }
            else if (key < tmp->parent->parent->parent->entry->key) {
                tmp = tmp->parent->parent->parent;
                splay->Splay(tmp->left, key);
            }
            else if (key > tmp->parent->parent->parent->entry->key) {
                tmp = tmp->parent->parent->parent;
                splay->Splay(tmp->right, key);
            }
            traversedList.push_back(key);
            if ((int)keys.size() == maxNumOfKeys) {
                keys.pop();
            }
            keys.push(key);
            return tmpvalue;
        }
    }
    void traverseNLROnAVL(void (*func)(K key, V value)) {
        avl->traverseNLR(func);
    }
    void traverseNLROnSplay(void (*func)(K key, V value)) {
        splay->traverseNLR(func);
    }
    void clear() {
        while (!keys.empty()) {
            keys.pop();
        }
        delete avl;
        delete splay;
    }
    class SplayTree {
    public:
        class Node {
            Entry* entry;
            Node* left;
            Node* right;
            Node* parent;
            typename AVLTree::Node* corr;
            friend class AVLTree;
            friend class BKUTree;
            friend class SplayTree;
            friend class AVLTree::Node;

            Node(Entry* entry = NULL, Node* parent = NULL, Node* left = NULL, Node* right = NULL) {
                this->entry = entry;
                this->parent = parent;
                this->left = left;
                this->right = right;
                this->corr = NULL;
            }
            ~Node() {
                if (entry != nullptr) delete entry;
                parent = nullptr;
                entry = nullptr;
                left = nullptr;
                right = nullptr;
                corr = nullptr;
            }
        };

    public:
        Node* root;
        Node* addedNode;
        SplayTree() {
            this->root = nullptr;
            this->addedNode = nullptr;
        }
        ~SplayTree() { this->clear(); addedNode = nullptr; }

        void add(Entry* entry, Node*& root) {
            if (root == nullptr) {
                root = new Node(entry);
                addedNode = root;
                return;
            }
            if (entry->key < root->entry->key) {
                if (root->left == nullptr) {
                    root->left = new Node(entry, root);
                    addedNode = root->left;
                    return;
                }
                add(entry, root->left);
            }
            else if (entry->key > root->entry->key) {
                if (root->right == nullptr) {
                    root->right = new Node(entry, root);
                    addedNode = root->right;
                    return;
                }
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
        }
        void rotL(Node*& root) {
            Node* tmp = root->right;
            root->right = tmp->left;
            tmp->left = root;
            root = tmp;
            root->parent = root->left->parent;
            root->left->parent = root;
            if (root->left->right != nullptr) root->left->right->parent = root->left;
        }
        void rotR(Node*& root) {
            Node* tmp = root->left;
            root->left = tmp->right;
            tmp->right = root;
            root = tmp;
            root->parent = root->right->parent;
            root->right->parent = root;
            if (root->right->left != nullptr) root->right->left->parent = root->right;
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
        V search(K key) {
            Node* tmp = this->root;
            while (tmp != nullptr && tmp->entry->key != key) {
                if (key < tmp->entry->key) tmp = tmp->left;
                else if (key > tmp->entry->key) tmp = tmp->right;
            }
            if (tmp == nullptr) {
                throw "Not found";
            }
            else {
                Splay(this->root, key);
            }
            return this->root->entry->value;
        }
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
        void clear(Node*& root) {
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
    class AVLTree {
    public:
        class Node {
            Entry* entry;
            Node* left;
            Node* right;
            BalanceValue balance;
            typename SplayTree::Node* corr;
            friend class AVLTree;
            friend class BKUTree;
            friend class SplayTree;
            friend class SplayTree::Node;

            Node(Entry* entry = NULL, Node* left = NULL, Node* right = NULL) {
                this->entry = entry;
                this->left = left;
                this->right = right;
                this->balance = EH;
                this->corr = nullptr;
            }
            ~Node() {
                if (entry != nullptr) delete entry;
                entry = nullptr;
                left = right = nullptr;
                corr = nullptr;
            }
        };

    public:
        Node* root;
        Node* addedNode;

        AVLTree() { this->root = nullptr; this->addedNode = nullptr; }
        ~AVLTree() { this->clear(); addedNode = nullptr; }

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
                this->addedNode = root;
            }
            else {
                if (entry->key == root->entry->key) {
                    throw "Duplicate key";
                }
                else if (entry->key < root->entry->key) {
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
        void add(K key, V value) {
            Entry* entry = new Entry(key, value);
            add(this->root, entry);
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
        void remove(K key) {
            remove(this->root, key);
        }
        typename SplayTree::Node* search(Node* root, K key, vector<K>& traversedList, bool start = 0) {
            if (start == 0) {
                Node* tmp = root;
                while (tmp != nullptr && tmp->entry->key != key) {
                    traversedList.push_back(tmp->entry->key);
                    if (key < tmp->entry->key) tmp = tmp->left;
                    else if (key > tmp->entry->key) tmp = tmp->right;
                }
                if (tmp == nullptr) {
                    search(root, key, traversedList, 1);
                }
                else {
                    return tmp->corr;
                }
            }
            else if (start == 1) {
                Node* tmp = this->root;
                while (tmp->entry->key != key) {
                    traversedList.push_back(tmp->entry->key);
                    if (key < tmp->entry->key) tmp = tmp->left;
                    else if (key > tmp->entry->key) tmp = tmp->right;
                }
                return tmp->corr;
            }
        }
        V search(K key) {
            Node* tmp = this->root;
            while (tmp != nullptr && tmp->entry->key != key) {
                if (key < tmp->entry->key) tmp = tmp->left;
                else if (key > tmp->entry->key) tmp = tmp->right;
            }
            if (tmp == nullptr) throw "Not found";
            else return tmp->entry->value;
        }
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
};
#endif
