#include <bits/stdc++.h>

using namespace std;
class Trie {
private:

public:
    struct Key {
        char c;

        Key(char ch) {
            c = ch;
        }

        bool operator==(const Key & key) const {
            return c == key.c;
        }
    };

    struct KeyHasher {
    public:
        size_t operator()(const Key& k) const
        {
            return hash<char>()(k.c);
        }
    };

    struct Node {
        Key* key;
        unordered_map<Key,struct Node*,KeyHasher> children;
        bool isEndWord;

        Node(Key* key) {
            this->key = key;
            this->children.reserve(26);
            this->children.max_load_factor(0.25);
            this->isEndWord = false;
        }

         Node* findChild(Key& k) {
             if (children.find(k) != children.end()) {
                 return children[k];
             }
            return nullptr;
        }

         void addChild(Node* node) {
            Key* k = node->key;
            children[*k] = node;
        }

    };

    Node* root;

     Trie() {
        root = new Node(new Key('\0'));
    }

    /** Inserts a word into the trie. */
     void insert(const string& word) {
        root = insert(root, 0, word);
    }

    Node* insert(Node* cur, int index, const string& word) {
        Node* newChildNode;
        Key key(word[index]);
        Node* matchingChild = cur->findChild(key);
        if (matchingChild != nullptr) {
            if (index == word.length()-1) {
                matchingChild->isEndWord = true;
                cur->addChild(matchingChild);
                return cur;
            }
            newChildNode = insert(matchingChild, index+1, word);
            cur->addChild(newChildNode);
        }
        else {
            newChildNode = new Node(&key);
            if (index == word.length()-1) {
                newChildNode->isEndWord = true;
                cur->addChild(newChildNode);
                return cur;
            }
            cur->addChild(insert(newChildNode, index+1, word));
        }
        return cur;
    }

    /** Returns if the word is in the trie. */
     bool search(const string& word) const {
        Node* cur = root;
        for (int i = 0; i < word.length(); i++) {
            Key key(word[i]);
            Node* child = cur->findChild(key);
            if (child == nullptr) {
                return false;
            }
            cur = child;
        }
        return cur->isEndWord;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(const string& prefix) const {
        Node *cur = root;
        for (int i = 0; i < prefix.length(); i++) {
            Key key(prefix[i]);
            Node *child = cur->findChild(key);
            if (child == nullptr) {
                return false;
            }
            cur = child;
        }
        return true;
    }
};

int main() {

    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("appef");
    trie.insert("beff");
    cout << "Search apple = " << trie.search("apple") << endl;
    cout << "Search app = " << trie.search("app") << endl;
    cout << "Search appef = " << trie.search("appef") << endl;
    cout << "startsWith appef = " << trie.startsWith("appef") << endl;
    cout << "startsWith appefjk = " << trie.startsWith("appefjk") << endl;
    cout << "search appefjk = " << trie.search("appefjk") << endl;
    cout << "search a = " << trie.search("a") << endl;
    cout << "startsWith a = " << trie.startsWith("a") << endl;
    cout << "search beff = " << trie.search("beff") << endl;
    cout << "startsWith beff = " << trie.startsWith("beff") << endl;
    cout << "startsWith b = " << trie.startsWith("b") << endl;
    cout << "search befff = " << trie.search("befff") << endl;
    cout << "startsWith befff = " << trie.startsWith("befff") << endl;
    return 0;
}
