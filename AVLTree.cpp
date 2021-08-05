//
// Created by arun07 on 25-10-2020.
//


/**
 * AVL Tree
 *
 * Duplicates Allowed
 * 
 *
 * Every Function Working
 * 
 */

#include <bits/stdc++.h>
using namespace std;
class AVLTree {

private:
    struct Node {
        int key, height, dupCnt, subTreeSize;
        struct Node *left, *right;

        Node(int d) {
            key = d;
            height = 1;
            dupCnt = 1;
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

    int szOfSubtree(Node *&node) {
        if (node == NULL) {
            return 0;
        }
        return node->subTreeSize;
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

        y->subTreeSize = szOfSubtree(y->left) + szOfSubtree(y->right) + y->dupCnt;
        x->subTreeSize = szOfSubtree(x->left) + szOfSubtree(x->right) + x->dupCnt;

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

        x->subTreeSize = szOfSubtree(x->left) + szOfSubtree(x->right) + x->dupCnt;
        y->subTreeSize = szOfSubtree(y->left) + szOfSubtree(y->right) + y->dupCnt;

        // Return new root
        return y;
    }

    // Get Balance factor of node N
    int getBalance(Node *&N) {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }

    int rank(Node *&root, int &key) {
        if (root == NULL) {
            return -1;
        }
        else if (root->key == (key)) {
            return szOfSubtree(root->left);
        }
        else if (root->key < (key)) {
            int r = rank(root->right, key);
            if (r != -1) {
                return szOfSubtree(root->left) + r + root->dupCnt;
            }
            return r;
        }
        else {
            return rank(root->left, key);
        }
    }

    Node* insert(Node *&node, int &key) {
        if (node == NULL)
            return (new Node(key));
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else {
            node->dupCnt++;
        }

        node->height = 1 + max(height(node->left),
                               height(node->right));
        node->subTreeSize = szOfSubtree(node->left) + szOfSubtree(node->right) + node->dupCnt;

        int balance = getBalance(node);
        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Left Case
        if (balance < -1 && key < node->right->key) {
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

    Node* deleteNode(Node *&root, int &key, bool &deleteCompletely) {
        if (root == NULL)
            return root;
        if (key < root->key)
            root->left = deleteNode(root->left, key, deleteCompletely);
        else if (key > root->key)
            root->right = deleteNode(root->right, key, deleteCompletely);
        else {
            if (root->dupCnt > 1 && !deleteCompletely) {
                root->dupCnt--;
            }
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
                    root->dupCnt = temp->dupCnt;

                    bool del = true;
                    root->right = deleteNode(root->right, temp->key, del);
                }
            }
        }

        // If the tree had only one node then return
        if (root == NULL)
            return root;

        root->height = max(height(root->left), height(root->right)) + 1;
        root->subTreeSize = szOfSubtree(root->left) + szOfSubtree(root->right) + root->dupCnt;

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

    // Iterative function to find inorder successor for given key in a BST
    Node* findSuccessor(Node *root, int &key) {
        Node *succ = NULL;
        if (root == NULL) {
            return NULL;
        }
        while (true) {
            if (key < (root->key)) // key < root.key
            {
                succ = root;
                root = root->left;
            }
            else if (key > (root->key)) // key > root.key
            {
                root = root->right;
            }
            else {
                if (root->right != NULL) {
                    succ = minValueNode(root->right);
                }
                break;
            }
            if (root == NULL) {
                break;
            }
        }
        return succ;
    }


    Node* findSuccessorWithEqualityConsideration(Node *root, int &key) {
        Node *succ = NULL;
        if (root == NULL) {
            return NULL;
        }
        while (true) {
            if (key < (root->key)) // key < root.key
            {
                succ = root;
                root = root->left;
            }
            else if (key > (root->key)) // key > root.key
            {
                root = root->right;
            } else {
                succ = root;
                break;
            }
            if (root == NULL) {
                break;
            }
        }
        return succ;
    }

    Node* findPredecessor(Node *root, int &key) {
        Node *predecessor = NULL;
        if (root == NULL) {
            return NULL;
        }
        while (true) {
            if (key < (root->key)) // key < root.key
            {
                root = root->left;
            }
            else if (key > (root->key)) // key > root.key
            {
                predecessor = root;
                root = root->right;
            }
            else {
                if (root->left != NULL) {
                    predecessor = findMaximum(root->left);
                }
                break;
            }
            if (root == NULL) {
                break;
            }
        }
        return predecessor;
    }

    Node* findPredecessorWithEqualityConsideration(Node *root, int &key) {
        Node *predecessor = NULL;
        if (root == NULL) {
            return NULL;
        }
        while (true) {
            if (key < (root->key)) // key < root.key
            {
                root = root->left;
            }
            else if (key > (root->key)) // key > root.key
            {
                predecessor = root;
                root = root->right;
            }
            else {
                predecessor = root;
                break;
            }
            if (root == NULL) {
                break;
            }
        }
        return predecessor;
    }

public:
    int size() {
        return szOfSubtree(root);
    }

    /**
     *
     * @param key
     * @return rank of key stating from zero. Ex: rank of minimum element will be zero. Returns -1 if key is not found in the tree
     */
     int rank(int key) {
        return rank(root, key);
    }

    /**
     *
     * @param i
     * @return key element whose rank(i) = key. Ex : for i == 0 , return minimum key. If i == tree.size(), return null.
     */
     int* select(int i) {
        Node *node = root;
        while (node != NULL) {
            int rank = szOfSubtree(node->left);
            if (i >= rank && i <= (rank + node->dupCnt - 1)) {
                return &node->key;
            }
            else if (i < rank) {
                node = node->left;
            }
            else {
                i -= (rank + node->dupCnt);
                node = node->right;
            }
        }
        return NULL;
    }

    void insertKey(int key) {
        root = insert(root, key);
    }

    void deleteKey(int key) {
         bool deleteCompletely = false;
         root = deleteNode(root, key, deleteCompletely);
    }

    /**
     * returns least element greater than key if present otherwise returns null
     *
     * @param key
     * @return
     */
     int* findSuccessor(int key) {
        Node* successor = findSuccessor(root, key);
        if (successor == NULL) {
            return NULL;
        }
        return &successor->key;
    }

    /**
     * returns least element greater than or Equal to key if present otherwise returns null
     *
     * @param key
     * @return
     */
     int* findSuccessorWithEqualityConsideration(int key) {
        Node *successorWithEqualityConsideration = findSuccessorWithEqualityConsideration(root, key);
        if (successorWithEqualityConsideration == NULL) {
            return NULL;
        }
        return &successorWithEqualityConsideration->key;
    }

    /**
     * returns greatest element lesser than key if present otherwise returns null
     *
     * @param key
     * @return
     */
     int* findPredecessor(int key) {
        Node *predecessor = findPredecessor(root, key);
        if (predecessor == NULL) {
            return NULL;
        }
        return &predecessor->key;
    }

    /**
     * returns greatest element lesser than or Equal to key if present otherwise returns null
     *
     * @param key
     * @return
     */
     int* findPredecessorWithEqualityConsideration(int key) {
        Node *predecessorWithEqualityConsideration = findPredecessorWithEqualityConsideration(root, key);
        if (predecessorWithEqualityConsideration == NULL) {
            return NULL;
        }
        return &predecessorWithEqualityConsideration->key;
    }
};

