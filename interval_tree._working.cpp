#include <bits/stdc++.h>

using namespace std;

struct Interval
{  
    static const int MIN_VALUE = -2e9;      
    int low, high, index;
    Interval(int low, int high, int index) {
        this->low = low;
        this->high = high;
        this->index = index;
    }
};

class IntervalTree {

private:
    struct Node {
        int key;
        // AVLTree *values;
        map<int,unordered_set<int>> mp;
        int highValue;
        int height, subTreeSize;
        struct Node *left, *right;

        Node(Interval d) {
            key = d.low;
            // values = new AVLTree();
            // values->insertKey(d.high);
            unordered_set<int> us;
            us.insert(d.index);
            mp.insert(make_pair(d.high, us));
            highValue = d.high;
            height = 1;
            subTreeSize = 1;
            left = NULL;
            right = NULL;
        }
    };

    Node *root = NULL;

    int height(Node *&N) {
        if (N == NULL)
            return 0;
        return N->height;
    }

    int highValue(Node *&N) {
        if (N == NULL) {
            return Interval::MIN_VALUE;
        }
        return N->highValue;
    }

    // A utility function to right rotate subtree rooted with y
    Node* rightRotate(Node *&y) {
        Node *x = y->left;
        Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        y->highValue = max((y->mp.rbegin())->first, max(highValue(y->left), highValue(y->right)));
        x->highValue = max((x->mp.rbegin())->first, max(highValue(x->left), highValue(x->right)));

        // Return new root
        return x;
    }

    // A utility function to left rotate subtree rooted with x
    Node* leftRotate(Node *&x) {
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        x->highValue = max((x->mp.rbegin())->first, max(highValue(x->left), highValue(x->right)));
        y->highValue = max((y->mp.rbegin())->first, max(highValue(y->left), highValue(y->right)));
        // Return new root
        return y;
    }

    // Get Balance factor of node N
    int getBalance(Node *&N) {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node* insert(Node *&node, Interval &key) {
        if (node == NULL)
            return (new Node(key));
        if (key.low < node->key)
            node->left = insert(node->left, key);
        else if (key.low > node->key)
            node->right = insert(node->right, key);
        else {
            if (node->mp.find(key.high) == node->mp.end()) {
                unordered_set<int> us;
                us.insert(key.index);
                node->mp.insert({key.high, us});
            }
            else {
                auto itr = node->mp.find(key.high);
                itr->second.insert(key.index);
            }
        }

        node->height = 1 + max(height(node->left),
                               height(node->right));
        node->highValue = max((node->mp.rbegin())->first, max(highValue(node->left), highValue(node->right)));

        int balance = getBalance(node);
        // Left Left Case
        if (balance > 1 && key.low < node->left->key)
            return rightRotate(node);
        // Right Right Case
        if (balance < -1 && key.low > node->right->key)
            return leftRotate(node);
        // Left Right Case
        if (balance > 1 && key.low > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Left Case
        if (balance < -1 && key.low < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    // node != NULL
    Node* minValueNode(Node *&node) {
        Node *current = node;
        while (current->left != NULL)
            current = current->left;

        return current;
    }

    /**
    * @param node can't be null
    * @return
    */
    Node* findMaximum(Node *&node) {
        while (node->right != NULL) {
            node = node->right;
        }
        return node;
    }

     Node* deleteNode(Node *&root, int &key) {
        if (root == NULL)
            return root;
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
                // node with only one child or no child
                if ((root->left == NULL) || (root->right == NULL)) {
                    Node *temp = NULL;
                    if (temp == root->left)
                        temp = root->right;
                    else
                        temp = root->left;
                    // No child case
                    if (temp == NULL) {
                        temp = root;
                        root = NULL;
                    }
                    else {
                        // One child case
                        root = temp; // Copy the contents of
                        // the non-empty child
                    }
                } else {
                    Node *temp = minValueNode(root->right);
                    root->key = temp->key;
                    root->right = deleteNode(root->right, temp->key);
                }
            
        }

        // If the tree had only one node then return
        if (root == NULL)
            return root;

        root->height = max(height(root->left), height(root->right)) + 1;
        root->highValue = max((root->mp.rbegin())->first, max(highValue(root->left), highValue(root->right)));

        int balance = getBalance(root);
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    Node* deleteInterval(Node *&root, Interval &key) {
        if (root == NULL)
            return root;
        if (key.low < root->key)
            root->left = deleteInterval(root->left, key);
        else if (key.low > root->key)
            root->right = deleteInterval(root->right, key);
        else {
            auto itr = root->mp.find(key.high);
            itr->second.erase(key.index);
            if (itr->second.size() == 0) {
                root->mp.erase(key.high);
            }
            debug(key.low, key.high, key.index); 
            if (root->mp.size() == 0) {
                // node with only one child or no child
                debug("Size zero");
                if ((root->left == NULL) || (root->right == NULL)) {
                    Node *temp = NULL;
                    if (temp == root->left)
                        temp = root->right;
                    else
                        temp = root->left;
                    // No child case
                    if (temp == NULL) {
                        debug("No child");
                        temp = root;
                        root = NULL;
                    }
                    else {
                        debug("One child");
                        // One child case
                        root = temp; // Copy the contents of
                        // the non-empty child
                    }
                } else {
                    debug("Two child");
                    Node *temp = minValueNode(root->right);

                    root->key = temp->key;
                    root->mp = temp->mp;
                    root->highValue = (temp->mp.rbegin())->first;

                    root->right = deleteNode(root->right, temp->key);
                }
            }
        }

        // If the tree had only one node then return
        if (root == NULL) {
            debug("Returned");
            return root;
        }

        root->height = max(height(root->left), height(root->right)) + 1;
        root->highValue = max((root->mp.rbegin())->first, max(highValue(root->left), highValue(root->right)));

        int balance = getBalance(root);
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    Interval* overlapping(Node *&root, pair<int,int> &interval) {
        if (root == NULL) {
            return NULL;
        }
        int mx_end = (root->mp.rbegin())->first;
        debug(mx_end);
        if (mx_end >= interval.first && interval.second >= root->key) {
            debug("Destination Found", root->key, mx_end);
            debug(*(root->mp.find(mx_end)->second.begin()));
            return new Interval(root->key, mx_end, *(root->mp.find(mx_end)->second.begin()));
        }
        else if (root->left != NULL && root->left->highValue >= interval.first) {
            return overlapping(root->left, interval);
        }
        else {
            return overlapping(root->right, interval);
        }
    }

public:

    IntervalTree() {
        root = NULL;
    }

    void insertKey(Interval key) {
        root = insert(root, key);
    }

    void deleteKey(Interval key) {
        root = deleteInterval(root, key);
    }

    Interval* overlapping(pair<int,int> interval) {
        return overlapping(root, interval);
    }
};