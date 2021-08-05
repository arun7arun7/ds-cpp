#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
ll INF;

class Min_Heap {
public:
    struct Node {
        int key;
        ll priority;

        Node(int key, ll priority) : key(key), priority(priority) {}
    };

    Min_Heap(int n) {
        heap_array.reserve(n);
        index_heap_array.reserve(n);
        index_heap_array.max_load_factor(0.25);
        size = 0;
    }

    void insert(Node* node) {
        heap_array[size] = node;
        index_heap_array[node->key] = size;
        up_heap(size);
        size++;
    }

    Node* poll() {
        if (size == 0) {
            return nullptr;
        }
        Node* top = heap_array[0];
        size--;
        if (size > 0) {
            heap_array[0] = heap_array[size];
            index_heap_array[heap_array[0]->key] = 0;
            sink_down(0);
        }
        return top;
    }

    void decrease_priority(int key, ll new_priority) {
        if (index_heap_array.find(key) != index_heap_array.end()) {
            int index = index_heap_array[key];
            heap_array[index] = new Node(key, new_priority);
            up_heap(index);
        }
    }

    Node* peek() {
        if (size == 0) {
            return nullptr;
        }
        return heap_array[0];
    }

    bool empty() {
        return size == 0;
    }

private:
    vector<Node*> heap_array;
    unordered_map<int,int> index_heap_array;
    int size;

    void up_heap(int index) {
        int parent_index = parent(index);
        while (parent_index != -1 && heap_array[index]->priority < heap_array[parent_index]->priority) {
            swap(index, parent_index);
            index = parent_index;
            parent_index = parent(index);
        }
    }

    void sink_down(int index) {
        int left_index = 2*index+1, right_index = 2*index+2;
        int min_index = -1;
        if (left_index < size && heap_array[index]->priority > heap_array[left_index]->priority) {
            min_index = left_index;
        }
        if (right_index < size && heap_array[index]->priority > heap_array[right_index]->priority) {
            if (min_index == -1 || heap_array[left_index]->priority > heap_array[right_index]->priority) {
                min_index = right_index;
            }
        }
        if (min_index != -1) {
            swap(index, min_index);
            sink_down(min_index);
        }
    }

    int parent(int index) {
        if (index % 2 != 0) {
            return index/2;
        }
        return index/2 - 1;
    }

    void swap(int index_1, int index_2) {
        Node* element_index_1 = heap_array[index_1];
        heap_array[index_1] = heap_array[index_2];
        heap_array[index_2] = element_index_1;

        index_heap_array[heap_array[index_1]->key] = index_1;
        index_heap_array[heap_array[index_2]->key] = index_2;
    }

};
